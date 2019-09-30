#ifndef DIALOGFILE_H
#define DIALOGFILE_H

#include <QDialog>

namespace Ui {
class Dialogfile;
}

class Dialogfile : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogfile(QWidget *parent = 0);
    ~Dialogfile();

private:
    Ui::Dialogfile *ui;
};

#endif // DIALOGFILE_H
