#include "dialogstruct.h"
#include "ui_dialogstruct.h"

Dialogstruct::Dialogstruct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogstruct)
{
    ui->setupUi(this);
}

Dialogstruct::~Dialogstruct()
{
    delete ui;
}
