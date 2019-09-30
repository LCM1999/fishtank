
#include "dialogfile.h"
#include "dialogprocess.h"
#include "dialogstruct.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <qstandarditemmodel.h>

#include <QDebug>


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
    this->model = new QStandardItemModel(ui->treeView_2);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("序号")<<QStringLiteral("进程名")<<QStringLiteral("当前位置"));
    ui->treeView_2->setModel(model);
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
        if(pthread != NULL){
            stopListingPro();
        }
        isListing = false;
    } else {
        ui->textBrowser->append("start listing");
        openListingInt3();
        openListingPro();
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

void MainWindow::refreshlist(vector<process_struct> proclist){
 //   vector<process_struct> proclist = data.value<vector<process_struct>>();
    qDebug("%d",proclist.size());
    model->clear();
    for(int i = 0 ;i< proclist.size(); i++) {
        //qDebug()<<this_procList.at(i).process_name;
        QStandardItem* itemProject = new QStandardItem(QString::number(proclist.at(i).pid));
        model->appendRow(itemProject);
        model->setItem(i,1,new QStandardItem(QString::fromStdString(proclist.at(i).process_name)));
        model->setItem(i,2,new QStandardItem(QString("%1").arg(proclist.at(i).current_proc,4,16,QLatin1Char('0'))));
    }
    ui->treeView_2->setModel(model);
}
