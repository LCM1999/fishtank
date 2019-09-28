#include "dialogfile.h"
#include "ui_dialogfile.h"

Dialogfile::Dialogfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogfile)
{
    ui->setupUi(this);
}

Dialogfile::~Dialogfile()
{
    delete ui;
}
