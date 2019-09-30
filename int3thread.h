#ifndef INT3THREAD_H
#define INT3THREAD_H

#include <QThread>
#include <QTextBrowser>
#include <QString>
#include <QtCore>


class int3Thread :public QThread
{
    Q_OBJECT

public:
    int3Thread(char* name);
    void run();
    void stop();
    bool isRun;
    QString vm_name;
signals:
    void textSig(QString s);

};

#endif // INT3THREAD_H
