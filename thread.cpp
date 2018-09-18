#include "thread.h"

#include <QTimer>
#include <QMutexLocker>

Thread::Thread()
{
    stopped = false;
}

void Thread::setMessage(const QString &message)
{
    messageStr = message;
}

void Thread::stop()
{
    stopped = true;
}

void Thread::run()
{
    while(!stopped)
    {
        qDebug()<<messageStr;
    }
    stopped = false;
    std::cerr<<std::endl;
}
