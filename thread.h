#ifndef THREAD_H
#define THREAD_H


#include <QThread>
#include <QtCore>
#include <QObject>
#include <QMutex>
#include <iostream>

using namespace std;

class Thread : public QThread
{
    Q_OBJECT
public:
    Thread();

    void setMessage(const QString &message);
    void stop();

protected:
    void run();

protected:
    QString messageStr;
    volatile bool stopped;
};

#endif // THREAD_H
