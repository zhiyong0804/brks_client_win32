#include <QDebug>
#include "userdialog.h"
#include "ui_userdialog.h"

#include "ui_style_sheet.h"
#include "userinfo.h"
#include "triplistdialog.h"
#include "moneydialog.h"

UserDialog::UserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDialog)
{
    ui->setupUi(this);

    updateUserInfo();
    initUI();
}

UserDialog::~UserDialog()
{
    delete ui;
}

void UserDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    // 设置UI风格
    ui->userButton->setStyleSheet(sheet_user_userButton);
    ui->mobiButton->setStyleSheet(sheet_user_mobiButton);
    ui->remainderButton->setStyleSheet(sheet_user_remainderButton);
    ui->tripButton->setStyleSheet(sheet_user_tripButton);
    ui->memberButton->setStyleSheet(sheet_user_memberButton);
    ui->honorButton->setStyleSheet(sheet_user_honorButton);

//    ui->settingButton->hide();
//    ui->logOffButton->hide();
}

void UserDialog::updateUserInfo()
{
    UserInfo *userInfo = UserInfo::getCurUserInfo();
    if(userInfo)
    {

        qDebug() << __FUNCTION__ << userInfo->account();
        qDebug() << __FUNCTION__ << userInfo->mobi();
        qDebug() << __FUNCTION__ << userInfo->remainder();
        qDebug() << __FUNCTION__ << userInfo->trip();

        ui->accountLabel->setText(userInfo->account());
        char charStr[100];
        sprintf(charStr, u8"%d摩币", userInfo->mobi());
        ui->mobiLabel->setText(charStr);

        sprintf(charStr, u8"余额 %0.1f元",userInfo->remainder());
        ui->remainderLabel->setText(charStr);

        sprintf(charStr, u8"里程数%0.1f公里", userInfo->trip());
        ui->tripLabel->setText(charStr);

    }
    else
    {
         qDebug() << __FUNCTION__ << "no user login";
    }
}

void UserDialog::on_logOffButton_clicked()
{
    UserInfo::requestLogOff(UserInfo::getDefaultAccount());           // 删除缺省登录的用户
    close();
}

void UserDialog::on_tripButton_clicked()
{
    TripListDialog *tripDialog = new TripListDialog(this);
    int resutl = tripDialog ->exec();
    if (resutl == QDialog::Accepted)
    {

    }
}

void UserDialog::on_remainderButton_clicked()
{
    MoneyDialog *dlg = new MoneyDialog(this);
    int resutl2 = dlg ->exec();
    updateUserInfo();
}
