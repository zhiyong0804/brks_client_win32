#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QWidget>
#include <bikemapview.h>
#include "timerutil.h"
#include "oneride.h"

namespace Ui {
class HomeWindow;
}
class ScanQRCodeDialog;
class UserDialog;
class HomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

    void updateOneRideInfo();

private slots:
    void on_requestLoginButton_clicked();

    void on_cameraScanButton_clicked();

    void on_user_center_button_clicked();

    void on_stopButton_clicked();

    void on_finishRideButton_clicked();

private:
    Ui::HomeWindow *ui;
    void initHomeUI(void);
    BikeMapView *bikeMapView_;
    ScanQRCodeDialog *pScanQRCodeDialog_ = nullptr;
    UserDialog *pUserDialog_ = nullptr;
    QString curAccount_;
    TimerUtil ridingTime_;
    OneRide *oneRide_ = nullptr;
};

#endif // HOMEWINDOW_H
