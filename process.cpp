#include "mainwindow.h"
#include "process.h"
#include <QDebug>
using namespace std;

vector<process_struct> getProcessList(char *argv){

    vmi_instance_t vmi;
        addr_t list_head = 0, cur_list_entry = 0, next_list_entry = 0;
        addr_t current_process = 0;
        char *procname = NULL;
        vmi_pid_t pid = 0;
        unsigned long tasks_offset = 0, pid_offset = 0, name_offset = 0;
        status_t status;

        vector<process_struct> process_list;
        process_struct this_proc;
//        /* this is the VM or file that we are looking at */
//        if (argc != 2) {
//            printf("Usage: %s <vmname>\n", argv[0]);
//            return 1;
//        } // if

        char *name = argv;
        char *name2;
        os_t os;

        /* initialize the libvmi library */
        if (VMI_FAILURE ==
                vmi_init_complete(&vmi, name, VMI_INIT_DOMAINNAME, NULL,
                                  VMI_CONFIG_GLOBAL_FILE_ENTRY, NULL, NULL)) {
            printf("Failed to init LibVMI library.\n");
            return process_list;
        }

        /* init the offset values */
        if (VMI_OS_LINUX == vmi_get_ostype(vmi)) {
            if ( VMI_FAILURE == vmi_get_offset(vmi, "linux_tasks", &tasks_offset) )
                goto error_exit;
            if ( VMI_FAILURE == vmi_get_offset(vmi, "linux_name", &name_offset) )
                goto error_exit;
            if ( VMI_FAILURE == vmi_get_offset(vmi, "linux_pid", &pid_offset) )
                goto error_exit;
        } else if (VMI_OS_WINDOWS == vmi_get_ostype(vmi)) {
            if ( VMI_FAILURE == vmi_get_offset(vmi, "win_tasks", &tasks_offset) )
                goto error_exit;
            if ( VMI_FAILURE == vmi_get_offset(vmi, "win_pname", &name_offset) )
                goto error_exit;
            if ( VMI_FAILURE == vmi_get_offset(vmi, "win_pid", &pid_offset) )
                goto error_exit;
        } else if (VMI_OS_FREEBSD == vmi_get_ostype(vmi)) {
            tasks_offset = 0;
            if ( VMI_FAILURE == vmi_get_offset(vmi, "freebsd_name", &name_offset) )
                goto error_exit;
            if ( VMI_FAILURE == vmi_get_offset(vmi, "freebsd_pid", &pid_offset) )
                goto error_exit;
        }

        /* pause the vm for consistent memory access */
        if (vmi_pause_vm(vmi) != VMI_SUCCESS) {
            printf("Failed to pause VM\n");
            goto error_exit;
        } // if

        /* demonstrate name and id accessors */
        name2 = vmi_get_name(vmi);
        vmi_mode_t mode;

        if (VMI_FAILURE == vmi_get_access_mode(vmi, NULL, 0, NULL, &mode))
            goto error_exit;

        if ( VMI_FILE != mode ) {
            uint64_t id = vmi_get_vmid(vmi);

            printf("Process listing for VM %s (id=%"PRIu64")\n", name2, id);
        } else {
            printf("Process listing for file %s\n", name2);
        }
        free(name2);

        os = vmi_get_ostype(vmi);

        /* get the head of the list */
        if (VMI_OS_LINUX == os) {
            /* Begin at PID 0, the 'swapper' task. It's not typically shown by OS
             *  utilities, but it is indeed part of the task list and useful to
             *  display as such.
             */
            if ( VMI_FAILURE == vmi_translate_ksym2v(vmi, "init_task", &list_head) )
                goto error_exit;

            list_head += tasks_offset;
        } else if (VMI_OS_WINDOWS == os) {

            // find PEPROCESS PsInitialSystemProcess
            if (VMI_FAILURE == vmi_read_addr_ksym(vmi, "PsActiveProcessHead", &list_head)) {
                printf("Failed to find PsActiveProcessHead\n");
                goto error_exit;
            }
        } else if (VMI_OS_FREEBSD == vmi_get_ostype(vmi)) {
            // find initproc
            if ( VMI_FAILURE == vmi_translate_ksym2v(vmi, "allproc", &list_head) )
                goto error_exit;
        }

        cur_list_entry = list_head;
        if (VMI_FAILURE == vmi_read_addr_va(vmi, cur_list_entry, 0, &next_list_entry)) {
            printf("Failed to read next pointer in loop at %"PRIx64"\n", cur_list_entry);
            goto error_exit;
        }

        if (VMI_OS_FREEBSD == vmi_get_ostype(vmi)) {
            // FreeBSD's p_list is not circularly linked
            list_head = 0;
            // Advance the pointer once
            status = vmi_read_addr_va(vmi, cur_list_entry, 0, &cur_list_entry);
            if (status == VMI_FAILURE) {
                printf("Failed to read next pointer in loop at %"PRIx64"\n", cur_list_entry);
                goto error_exit;
            }
        }

        /* walk the task list */
        while (1) {

            current_process = cur_list_entry - tasks_offset;

            /* Note: the task_struct that we are looking at has a lot of
             * information.  However, the process name and id are burried
             * nice and deep.  Instead of doing something sane like mapping
             * this data to a task_struct, I'm just jumping to the location
             * with the info that I want.  This helps to make the example
             * code cleaner, if not more fragile.  In a real app, you'd
             * want to do this a little more robust :-)  See
             * include/linux/sched.h for mode details */

            /* NOTE: _EPROCESS.UniqueProcessId is a really VOID*, but is never > 32 bits,
             * so this is safe enough for x64 Windows for example purposes */
            vmi_read_32_va(vmi, current_process + pid_offset, 0, (uint32_t*)&pid);

            procname = vmi_read_str_va(vmi, current_process + name_offset, 0);

            if (!procname) {
                printf("Failed to find procname\n");
                goto error_exit;
            }

            /* print out the process name */
            printf("[%5d] %s (struct addr:%"PRIx64")\n", pid, procname, current_process);
            //qDebug()<<procname;
            this_proc.pid = pid;
            this_proc.process_name = procname;
            this_proc.current_proc = current_process;

            process_list.insert(process_list.end(),this_proc);

            if (procname) {
                free(procname);
                procname = NULL;
            }

            if (VMI_OS_FREEBSD == os && next_list_entry == list_head) {
                break;
            }

            /* follow the next pointer */
            cur_list_entry = next_list_entry;
            status = vmi_read_addr_va(vmi, cur_list_entry, 0, &next_list_entry);
            if (status == VMI_FAILURE) {
                printf("Failed to read next pointer in loop at %"PRIx64"\n", cur_list_entry);
                goto error_exit;
            }
            /* In Windows, the next pointer points to the head of list, this pointer is actually the
             * address of PsActiveProcessHead symbol, not the address of an ActiveProcessLink in
             * EPROCESS struct.
             * It means in Windows, we should stop the loop at the last element in the list, while
             * in Linux, we should stop the loop when coming back to the first element of the loop
             */
            if (VMI_OS_WINDOWS == os && next_list_entry == list_head) {
                break;
            } else if (VMI_OS_LINUX == os && cur_list_entry == list_head) {
                break;
            }
        };

        return process_list;

    error_exit:
        /* resume the vm */
        vmi_resume_vm(vmi);

        /* cleanup any memory associated with the LibVMI instance */
        vmi_destroy(vmi);

        return process_list;
}
