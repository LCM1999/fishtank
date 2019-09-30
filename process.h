#ifndef PROCESS_H
#define PROCESS_H

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <inttypes.h>
#include <vector>

#include <libvmi/libvmi.h>

using namespace std;

struct process_struct
{
    process_struct(){}
    vmi_pid_t pid;
    std::string process_name;
    addr_t current_proc;
};
Q_DECLARE_METATYPE(vector<process_struct>);

vector<process_struct> getProcessList(char* argv);

#endif // PROCESS_H
