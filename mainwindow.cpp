
#include "dialogfile.h"
#include "dialogprocess.h"
#include "dialogstruct.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->vm_name = NULL;
    this->initTreeView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

char *MainWindow::qString2char(QString str)
{
    char* s;
    QByteArray arr = str.toLatin1();
    s = arr.data();
    return s;
}




void MainWindow::on_pushButton_2_clicked()
{
    Dialogstruct* dialog = new Dialogstruct(this);
    dialog->show();
}

void MainWindow::on_pushButton_clicked()
{
    Dialogfile* dialog = new Dialogfile(this);
    dialog->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    Dialogprocess* dialog = new Dialogprocess(this);
    dialog->show();
}
