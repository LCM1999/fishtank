#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "ui_mainwindow.h"
#include "int3thread.h"

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
    void on_listing_triggered();
    void on_action_4_triggered();
    void on_action_6_triggered();
    void on_textBrowser_2_textChanged();
    void updateText(QString s);

private:
    Ui::MainWindow *ui;
    QString* vm_name;
    int3Thread* thread_listing_int3;
    bool isListing;
    void initTreeView();
    void openListingInt3();
    void closeListingInt3();
};
#endif // MAINWINDOW_H
