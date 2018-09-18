#include <QDebug>
#include "oneride.h"

OneRide::OneRide(FunPtr funptr, void *user):
    QObject(nullptr),
    funptr_(funptr),
    user_(user),
    mileage_(0.0),
    cost_(1.0),
    callbackTimer_(nullptr)

{

}
//OneRide::OneRide():
//    QObject(nullptr)
//{}

OneRide::~OneRide()
{
    if(callbackTimer_)
    {
        callbackTimer_->stop();
        delete callbackTimer_;
        callbackTimer_ = nullptr;
    }

}

int OneRide::startRide()
{
    startTime_ = QDateTime::currentDateTime();
    qDebug() << __FUNCTION__ << " " <<  __LINE__;
    rideTimer_.reset();
    qDebug() << __FUNCTION__ << " " <<  __LINE__;
    startTimer();
    return 0;
}

int OneRide::finishRide()
{
    finishTime_ = QDateTime::currentDateTime();
    return 0;
}

QDateTime OneRide::startTime() const
{
    return startTime_;
}

QDateTime OneRide::finishTime() const
{
    return finishTime_;
}

int OneRide::durationSecond()
{
    durationSecond_ = rideTimer_.elapsed_seconds();
    return durationSecond_;
}

int OneRide::durationMinute()
{
    durationSecond_ = rideTimer_.elapsed_seconds();
    return durationSecond_ / 60;
}

float OneRide::cost() const
{
    return cost_;
}

float OneRide::consumeCalorie() const
{
    return consumeCalorie_;
}

void OneRide::on_timerInterval()
{
//    qDebug() << __FUNCTION__ << "mileage_: "<< mileage_;
   funptr_(user_);              // 执行回调函数
    mileage_ += 0.008;
}

void OneRide::startTimer()
{
    if(!callbackTimer_)
    {
        callbackTimer_ = new QTimer();
        callbackTimer_->setInterval(1000);
        connect(callbackTimer_, SIGNAL(timeout()), this, SLOT(on_timerInterval()));
    }
    else
    {
        callbackTimer_->stop();
    }
    callbackTimer_->start(1000);        // 开始触发
}

float OneRide::mileage() const
{
    return mileage_;
}
