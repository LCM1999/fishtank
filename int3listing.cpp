#include "mainwindow.h"
#include "int3thread.h"
#include <QDebug>
void MainWindow::openListingInt3() {
    QByteArray arr = vm_name->toLatin1();
    char* str = arr.data();
    qDebug()<<str;
    thread_listing_int3 = new int3Thread(str,ui->textBrowser_2);
    thread_listing_int3->start();
}
void MainWindow::closeListingInt3() {
    thread_listing_int3->stop();
}
