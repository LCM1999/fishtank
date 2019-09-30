#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QThread>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStringLiteral>
#include <QString>
#include "process.h"


class process_thread : public QThread{
    Q_OBJECT
public:
    process_thread(char* name, QTreeView* treeV);
    void run();
    void stop();
    bool isRun;
    QString vm_name;
    QStandardItemModel* model;

signals:
    void refresh(vector<process_struct> proclist);
};

#endif // PROCESSTHREAD_H
