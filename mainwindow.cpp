
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
    ui->textBrowser->append("software is working!");
    ui->textBrowser->append("XEN is working!");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->append("show Dialogstruct");
    Dialogstruct* dialog = new Dialogstruct(this);
    dialog->show();
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->append("show Dialogfile");
    Dialogfile* dialog = new Dialogfile(this);
    dialog->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textBrowser->append("show Dialogprocess");
    Dialogprocess* dialog = new Dialogprocess(this);
    dialog->show();
}

void MainWindow::on_listing_triggered()
{
    if(isListing) {
        if(thread_listing_int3 != NULL) {
            ui->textBrowser->append("stop listing");
            closeListingInt3();
        }
        isListing = false;
    } else {
        ui->textBrowser->append("start listing");
        openListingInt3();
        isListing = true;
    }
//    QMessageBox::about(this,"asd","asdas");
}

void MainWindow::on_action_4_triggered()
{
    Dialogstruct* dialog = new Dialogstruct(this);
    dialog->show();
}

void MainWindow::on_action_6_triggered()
{
    Dialogfile* dialog = new Dialogfile(this);
    dialog->show();
}

void MainWindow::on_textBrowser_2_textChanged()
{
    ui->textBrowser_2->moveCursor(QTextCursor::End);
}

void MainWindow::updateText(QString s)
{
    ui->textBrowser_2->append(s);
}
