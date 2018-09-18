#ifndef ONERIDE_H
#define ONERIDE_H
#include <QDateTime>
#include <QTimer>
#include <QObject>
#include "timerutil.h"

typedef void (*FunPtr)(void *user);   //这样只是定义一个函数指针类型

/**
 * @brief 记录一次骑行，包括起始时间，结束时间，骑行时长，消耗卡路里，计费情况
 */
class OneRide : public QObject
{
    Q_OBJECT
public:
    const int kCallbackInterval = 1000;         // 回调间隔
public:
   explicit OneRide(FunPtr funptr, void *user);
    // explicit OneRide();
    ~OneRide();
    int startRide();
    int finishRide();
    QDateTime startTime() const;

    QDateTime finishTime() const;

    int durationMinute() ;
    int durationSecond() ;
    float cost() const;

    float consumeCalorie() const;
    float mileage() const;

private slots:
    void on_timerInterval();
private:
    void startTimer();
    QDateTime startTime_;       // 骑行起始时间
    QDateTime finishTime_;      // 骑行结束时间
    int durationSecond_;        // 骑行持续时间，单位为毫秒
    float cost_ ;                // 计费情况, 计费规则由外部传入
    float consumeCalorie_;      // 消耗的卡路里
    TimerUtil rideTimer_;           // 计算骑行时长
    float mileage_;             // 记录单次骑行里程数
    QTimer *callbackTimer_;

    // 回调函数及其参数
    void *user_;
    FunPtr funptr_;

    // 回调间隔
};

#endif // ONERIDE_H
