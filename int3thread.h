#ifndef INT3THREAD_H
#define INT3THREAD_H

#include <QThread>
#include <QTextBrowser>
#include <QString>



class int3Thread : public QThread
{
public:
    int3Thread(char* name, QTextBrowser* textBrowser);
    void run();
    void stop();
    bool isRun;
    QString vm_name;
    QTextBrowser* textBrowser;

};

#endif // INT3THREAD_H
