#ifndef DIALOGPROCESS_H
#define DIALOGPROCESS_H

#include <QDialog>

namespace Ui {
class Dialogprocess;
}

class Dialogprocess : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogprocess(QWidget *parent = 0);
    ~Dialogprocess();

private:
    Ui::Dialogprocess *ui;
    void initTreeView();
};

#endif // DIALOGPROCESS_H
