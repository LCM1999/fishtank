#include "dialogprocess.h"
#include "ui_dialogprocess.h"

#include <QStandardItemModel>
#include <QStringLiteral>

Dialogprocess::Dialogprocess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogprocess)
{
    ui->setupUi(this);
    initTreeView();
}

Dialogprocess::~Dialogprocess()
{
    delete ui;
}
void Dialogprocess::initTreeView() {
    QStandardItemModel* model = new QStandardItemModel(ui->treeView);
    model->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("序号")<<QStringLiteral("进程名"));

    for(int i = 0 ;i< 10; i++) {
        QStandardItem* itemProject = new QStandardItem(QString::number(i));
        model->appendRow(itemProject);
        switch (i) {
        case 0:
            model->setItem(i,1,new QStandardItem(QStringLiteral("init")));
            break;
        case 1:
            model->setItem(i,1,new QStandardItem(QStringLiteral("ipaddr")));
            break;
        case 2:
            model->setItem(i,1,new QStandardItem(QStringLiteral("natapp")));
            break;
        case 3:
            model->setItem(i,1,new QStandardItem(QStringLiteral("iptable")));
            break;
        case 4:
            model->setItem(i,1,new QStandardItem(QStringLiteral("wine")));
            break;
        case 5:
            model->setItem(i,1,new QStandardItem(QStringLiteral("qq")));
            break;
        case 6:
            model->setItem(i,1,new QStandardItem(QStringLiteral("wang")));
            break;
        case 7:
            model->setItem(i,1,new QStandardItem(QStringLiteral("ree")));
            break;
        case 8:
            model->setItem(i,1,new QStandardItem(QStringLiteral("res")));
            break;
        case 9:
            model->setItem(i,1,new QStandardItem(QStringLiteral("rslroot")));
            break;
        default:
            break;
        }
    }
    ui->treeView->setModel(model);
}
