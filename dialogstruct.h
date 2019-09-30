#ifndef DIALOGSTRUCT_H
#define DIALOGSTRUCT_H

#include <QDialog>

namespace Ui {
class Dialogstruct;
}

class Dialogstruct : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogstruct(QWidget *parent = 0);
    ~Dialogstruct();

private:
    Ui::Dialogstruct *ui;
};

#endif // DIALOGSTRUCT_H
