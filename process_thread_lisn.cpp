#include "mainwindow.h"
#include "processthread.h"
#include <QDebug>
void MainWindow::openListingPro() {
    pthread = new process_thread((vm_name->toLatin1()).data(),ui->treeView_2);
    connect(pthread,SIGNAL(refresh(vector<process_struct>)),this,SLOT(refreshlist(vector<process_struct>)));
    pthread->start();
}
void MainWindow::stopListingPro() {
    pthread->stop();
}
