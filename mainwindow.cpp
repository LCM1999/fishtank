
#include "dialogfile.h"
#include "dialogprocess.h"
#include "dialogstruct.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->vm_name = NULL;
    this->isListing = false;
    this->thread_listing_int3 = NULL;
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

void MainWindow::on_listing_triggered()
{
    if(isListing) {
        if(thread_listing_int3 != NULL) {
            closeListingInt3();
        }
        isListing = false;
    } else {
        openListingInt3();
        isListing = true;
    }
//    QMessageBox::about(this,"asd","asdas");
}
