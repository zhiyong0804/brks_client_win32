#include "logindialog.h"
#include "ui_logindialog.h"

#include "ui_style_sheet.h"
#include "userinfo.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    initUI();

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

int LoginDialog::loginSuccessful()
{
    QString account = ui->accountEdit->text();
    QString verifyCode = ui->passwordEdit->text();
    if(!account.isEmpty())
    {
        //UserInfo *userInfo = new UserInfo(account);
       // UserInfo::setDefaultAccount(userInfo->account());
        UserInfo::requestLogin(account, verifyCode);
    }
    return 0;
}

void LoginDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    // 初始化UI
    ui->wechatButton->setStyleSheet(sheet_login_wechatButton);
    ui->weiboButton->setStyleSheet(sheet_login_weiboButton);
}

int LoginDialog::startCalculateRemainTime(int ramainTime)
{
    if(!timer_)
    {
        timer_ = new QTimer();
        timer_->setInterval(1000);
        connect(timer_, SIGNAL(timeout()), this, SLOT(on_updateVerfiyCodeReaminTime()));
    }
    else
    {
        timer_->stop();
    }
    remainTime_ = ramainTime;
    timer_->start(1000);        // 开始触发
    return 0;
}

void LoginDialog::on_loginButton_clicked()
{
    if(bVerifyCodeValid_)       // 验证码处于有效时间范围
    {
        // 1. 验证短信

        // 2.在本地创建账号信息
        loginSuccessful();
        done(Accepted);
    }
    close();
}

void LoginDialog::on_pushButton_clicked()
{

}

void LoginDialog::on_updateVerfiyCodeReaminTime()
{
    if(remainTime_-->0)
    {
        char charStr[100];
        sprintf(charStr, u8"剩余%d秒", remainTime_);
        ui->reqVerifyCodeButton->setText(charStr);

    }
    else                                            // 验证码超时失效
    {
        timer_->stop();
        remainTime_ = -1;
        ui->reqVerifyCodeButton->setStyleSheet(QString::fromUtf8("font: 10pt \"\351\273\221\344\275\223\";\n"
"color: rgb(255, 255, 255);background-color: rgb(255, 85, 0);"));
        ui->reqVerifyCodeButton->setText(u8"重发验证码");
        bVerifyCodeValid_ = false;
        ui->reqVerifyCodeButton->setEnabled(true);
    }
}

void LoginDialog::on_reqVerifyCodeButton_clicked()
{
    if(!bVerifyCodeValid_)
    {
        bVerifyCodeValid_ = true;
        ui->reqVerifyCodeButton->setEnabled(false);
        ui->reqVerifyCodeButton->setStyleSheet(QString::fromUtf8("font: 10pt \"\351\273\221\344\275\223\";\n"
"color: rgb(255, 255, 255);"));
        startCalculateRemainTime(kVerifyCodeResentTime);
    }
}
