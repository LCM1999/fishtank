#include "int3thread.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <inttypes.h>
#include <signal.h>

#include <libvmi/libvmi.h>
#include <libvmi/events.h>
#include <QDebug>
#include <QMessageBox>
vmi_event_t interrupt_event;

event_response_t int3_cb(vmi_instance_t vmi, vmi_event_t *event)
{
    vmi = vmi;
    printf("Int 3 happened: GFN=%"PRIx64" RIP=%"PRIx64" Length: %"PRIu32"\n",
           event->interrupt_event.gfn, event->interrupt_event.gla,
           event->interrupt_event.insn_length);

    /* This callback assumes that all INT3 events are caused by
     *  a debugger or similar inside the guest, and therefore
     *  unconditionally reinjects the interrupt.
     */
    event->interrupt_event.reinject = 1;

    /*
     * By default int3 instructions have length of 1 byte unless
     * there are prefixes attached. As adding prefixes to int3 have
     * no effect, under normal circumstances no legitimate compiler/debugger
     * would add any. However, a malicious guest could add prefixes to change
     * the instruction length. Older Xen versions (prior to 4.8) don't include this
     * information and thus this length is reported as 0. In those cases the length
     * have to be established manually, or assume a non-malicious guest as we do here.
     */
    if ( !event->interrupt_event.insn_length )
        event->interrupt_event.insn_length = 1;

    return 0;
}

static int interrupted = 0;
static void close_handler(int sig)
{
    interrupted = sig;
}

int3Thread::int3Thread(char* name,QTextBrowser* textBrowser)
{
    isRun = false;
    qDebug()<<"name::"<<name;
    this->vm_name = QString(name);
    qDebug()<<"name::"<<this->vm_name;
    this->textBrowser = textBrowser;
}

void int3Thread::stop() {
    isRun = false;
}

void int3Thread::run() {
    isRun = true;
    vmi_instance_t vmi;
    struct sigaction act;
    act.sa_handler = close_handler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction(SIGHUP,  &act, NULL);
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT,  &act, NULL);
    sigaction(SIGALRM, &act, NULL);

    qDebug()<<vm_name;
    QByteArray arr = vm_name.toLatin1();

    char *name = arr.data();

    if(name == NULL) {
        textBrowser->append("Error,Please select VM");
        return;
    }

    // Initialize the libvmi library.
    if (VMI_FAILURE ==
            vmi_init(&vmi, VMI_XEN, (void*)name, VMI_INIT_DOMAINNAME | VMI_INIT_EVENTS, NULL, NULL)) {
        textBrowser->append("Failed to init LibVMI library.");
        return ;
    }

    textBrowser->append("LibVMI init succeeded!");

    /* Register event to track INT3 interrupts */
    memset(&interrupt_event, 0, sizeof(vmi_event_t));
    interrupt_event.version = VMI_EVENTS_VERSION;
    interrupt_event.type = VMI_EVENT_INTERRUPT;
    interrupt_event.interrupt_event.intr = INT3;
    interrupt_event.callback = int3_cb;

    vmi_register_event(vmi, &interrupt_event);

    textBrowser->append("Waiting for events...\n");
    while (!interrupted && isRun) {
        vmi_events_listen(vmi,500);
    }
    textBrowser->append("Finished with test.\n");
    // cleanup any memory associated with the libvmi instance
    vmi_destroy(vmi);
    return ;
}
