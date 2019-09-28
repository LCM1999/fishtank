#include "mainwindow.h"

#include <QMessageBox>
#include <QString>
#include <QStringLiteral>
#include <qstandarditemmodel.h>
#include <QAbstractItemModel>

void MainWindow::initTreeView() {
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("序号")<<QStringLiteral("虚拟机名"));

    for(int i = 0 ;i< 3; i++) {
        QStandardItem* itemProject = new QStandardItem(QString::number(i));
        model->appendRow(itemProject);
        if(i == 2) {
            model->setItem(i,1,new QStandardItem(QStringLiteral("win7")));
        }else {
            model->setItem(i,1,new QStandardItem(QStringLiteral("ubuntu14.04")));
        }
    }
    ui->treeView->setModel(model);

    QStandardItemModel* model1 = new QStandardItemModel(ui->treeView_bin);
    model1->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("文件路径")<<QStringLiteral("二进制名"));
    connect(ui->treeView,SIGNAL(clicked( const QModelIndex)),this,SLOT(OnlineTreeViewClick(const QModelIndex)));

    for(int i = 0 ;i< 3; i++) {
        QStandardItem* itemProject = new QStandardItem(QString("/local/my"));
        model1->appendRow(itemProject);
        if(i == 2) {
            model1->setItem(i,1,new QStandardItem(QStringLiteral("rootkit")));
        }else {
            model1->setItem(i,1,new QStandardItem(QStringLiteral("tmep")));
        }
    }
    ui->treeView_bin->setModel(model1);
    connect(ui->treeView_bin,SIGNAL(clicked( const QModelIndex)),this,SLOT(OnlineTreeViewClickBin(const QModelIndex)));
}

void MainWindow::OnlineTreeViewClick(const QModelIndex & index){

    QAbstractItemModel* m=(QAbstractItemModel*)index.model();
    for(int columnIndex = 0; columnIndex < m->columnCount(); columnIndex++)
    {
        QModelIndex x=m->index(index.row(),columnIndex);
        QString s= x.data().toString();
        QMessageBox::about(this,s,s);
    }
}

void MainWindow::OnlineTreeViewClickBin(const QModelIndex & index){

    QAbstractItemModel* m=(QAbstractItemModel*)index.model();
    for(int columnIndex = 0; columnIndex < m->columnCount(); columnIndex++)
    {
        QModelIndex x=m->index(index.row(),columnIndex);
        QString s= x.data().toString();
        QMessageBox::about(this,s,s);
    }
}
