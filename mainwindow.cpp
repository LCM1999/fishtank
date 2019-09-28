
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
    this->initTreeView();
}

MainWindow::~MainWindow()
{
    delete ui;
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
