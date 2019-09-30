#include "mainwindow.h"
#include "process.h"
#include "processthread.h"
#include <QMetaType>

#include <QDebug>

using namespace std;

process_thread::process_thread(char *name, QTreeView *treeV){
    this->vm_name = QString(name);
    this->isRun = true;
    QStandardItemModel* model = new QStandardItemModel(treeV);
    this->model = model;
    qRegisterMetaType<vector<process_struct>>("vector<process_struct>");
}

void process_thread::run(){
    vector<process_struct> this_procList;
    while(isRun){
        this_procList= getProcessList((vm_name.toLatin1()).data());
//        QVariant data;
//        data.setValue(this_procList);
        emit refresh(this_procList);
        this->sleep(5);
    }
}

void process_thread::stop(){
    isRun = false;
}

