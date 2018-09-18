#include "homewindow.h"
#include "ui_homewindow.h"

#include "ui_style_sheet.h"
#include "logindialog.h"
#include "config.h"
#include "scanqrcodedialog.h"
#include "userdialog.h"
#include "userinfo.h"
#include "moneydialog.h"
HomeWindow::HomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWindow),
    oneRide_(nullptr)
{
    ui->setupUi(this);

    if(UserInfo::defaultLogin() == 0)   // 登录缺省的账号
    {
        ui->tipLoginWidget->hide(); // 登录成功则隐藏提示登录框
    }

    initHomeUI();
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::updateOneRideInfo()
{
    if(oneRide_)
    {
        char charStr[100];

        // 骑行时间
        int hours;
        int minutes;
        int seconds;
        seconds = oneRide_->durationSecond();
        hours = seconds / 60 / 60;
        minutes = seconds / 60;
        seconds = seconds % 60;

        if(hours > 0)
            sprintf(charStr, u8"时间 %02d:%02d:%02d", hours, minutes, seconds);
        else
            sprintf(charStr, u8"时间 %02d:%02d", minutes, seconds);
        ui->timeLabel->setText(charStr);
//        qDebug() << "timeLabel: "<< charStr;

        // 骑行里程
        sprintf(charStr, u8"里程 %0.1f公里", oneRide_->mileage());
        ui->tripLabel->setText(charStr);
//       qDebug() << "tripLabel: "<< charStr;
        // 骑行费用
        sprintf(charStr, u8"费用 %0.1f元", oneRide_->cost());
        ui->moneyLabel->setText(charStr);
//        qDebug() << "moneyLabel: "<< charStr;
    }
}

void HomeWindow::initHomeUI()
{
    ui->user_center_button->setStyleSheet(sheet_home_user_center_icon);
    ui->messages_button->setStyleSheet(sheet_home_messages_icon);
    ui->cameraScanButton->setStyleSheet(sheet_home_bike_scan_b);
    ui->tipLoginWidget->setWindowOpacity(1);          // 设置提示登录栏透明

    // 修改标题
    setWindowTitle(tr(kAppName.c_str()));
    //setWindowFlags(Qt::WindowCloseButtonHint);
    ui->bikeButton->setText(tr(kAppName.c_str()));
    ui->bikeButton->setEnabled(false);

    // 显示位置按钮
    ui->locationButton->setStyleSheet(sheet_locationButton);

    // 显示地图
    bikeMapView_ = new BikeMapView();
    QVBoxLayout *mapLayout = ui->stackedWidget->currentWidget()->findChild<QVBoxLayout *>("mapLayout");
    mapLayout->addWidget(bikeMapView_);

    ui->ridingInfowidget->setGeometry(QRect(15, 110, 520, 70));
    ui->ridingInfowidget->hide();
}

void HomeWindow::on_requestLoginButton_clicked()
{
    //    LoginDialog loginDialog(this);
    //    loginDialog.show();
    QDialog *login = new LoginDialog(this);

    int resutl = login ->exec();
    if (resutl == QDialog::Accepted)
    {
        qDebug() << __FUNCTION__ << " You Choose Ok";
        if(UserInfo::getCurUserInfo())
            ui->tipLoginWidget->hide();     // 能够获取到登录用户的信息则说明已经登录成功
        qDebug() << __FUNCTION__ << " user:" << UserInfo::getDefaultAccount();
    }
    else
    {
        qDebug() << __FUNCTION__ << " You Choose Cancel";
    }
}
void updateOneRideInfoExt(void *user)
{
    ((HomeWindow *)user)->updateOneRideInfo();
}

void HomeWindow::on_cameraScanButton_clicked()
{
    if(pScanQRCodeDialog_)
    {
        pScanQRCodeDialog_->show();
        return;
    }
    pScanQRCodeDialog_ = new ScanQRCodeDialog(this);

    int resutl = pScanQRCodeDialog_ ->exec();
    if (resutl == QDialog::Accepted)
    {
        qDebug() << __FUNCTION__ << " You Choose Ok";

        oneRide_ = new OneRide(updateOneRideInfoExt, this);
        qDebug() << __FUNCTION__ << " " <<  __LINE__;
        oneRide_->startRide();
        qDebug() << __FUNCTION__ << " " <<  __LINE__;
        // 隐藏扫描按钮
        ui->scanWidget->hide();
        qDebug() << __FUNCTION__ << " " <<  __LINE__;
        // 显示骑行时间并启动计数器
        ui->ridingInfowidget->show();
        qDebug() << __FUNCTION__ << " " <<  __LINE__;
    }
    else
    {
        qDebug() << __FUNCTION__ << " You Choose Cancel";
    }
    delete pScanQRCodeDialog_;
    pScanQRCodeDialog_ = nullptr;
}

void HomeWindow::on_user_center_button_clicked()
{
    if(pUserDialog_)
    {
        pUserDialog_->show();
        return;
    }
    pUserDialog_ = new UserDialog(this);

    int resutl = pUserDialog_ ->exec();
    if (resutl == QDialog::Accepted)
    {
        qDebug() << __FUNCTION__ << " You Choose Ok";

    }
    else
    {
        qDebug() <<__FUNCTION__ << " You Choose Cancel";
    }
    delete pUserDialog_;
    pUserDialog_ = nullptr;

    if(!UserInfo::getCurUserInfo())
    {
        ui->tipLoginWidget->show();
    }
}

void HomeWindow::on_stopButton_clicked()
{
    ui->ridingInfowidget->hide();
    ui->scanWidget->show();
}

void HomeWindow::on_finishRideButton_clicked()
{
    // 关闭骑行
    if(oneRide_)
    {
        oneRide_->finishRide();
        // 显示骑行时间以及扣款金额
        UserInfo *userInfo = UserInfo::getCurUserInfo();
        // 修改里程数
        float trip = 0;
        trip = userInfo->trip();
        trip += oneRide_->mileage();
        userInfo->setTrip(trip);
        // 修改余额
        float remainder = 0;
        remainder = userInfo->remainder();
        remainder -= oneRide_->cost();
        userInfo->setRemainder(remainder);
        // 修改摩币
        int mobi = 0;
        mobi = userInfo->mobi();
        mobi +=1;
        userInfo->setMobi(mobi);
        userInfo->sync();           // 将数据写入的文件中
        delete oneRide_;
        oneRide_ = nullptr;

        // 隐藏
        ui->ridingInfowidget->hide();
        ui->scanWidget->show();
    }
}
