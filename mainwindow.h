#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //tools
    char* qString2char(QString str);

private slots:
    void OnlineTreeViewClick(const QModelIndex & index);
    void OnlineTreeViewClickBin(const QModelIndex & index);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
private:
    Ui::MainWindow *ui;
    char* vm_name;
    void initTreeView();
};

#endif // MAINWINDOW_H
