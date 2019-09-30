#include "mainwindow.h"
#include "int3thread.h"
#include <QDebug>
void MainWindow::openListingInt3() {
    QByteArray arr = vm_name->toLatin1();
    char* str = arr.data();
    qDebug()<<str;
    thread_listing_int3 = new int3Thread(str);
    connect(thread_listing_int3,SIGNAL(textSig(QString)),this,SLOT(updateText(QString)));
    thread_listing_int3->start();
}
void MainWindow::closeListingInt3() {
    thread_listing_int3->stop();
}
