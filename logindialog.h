#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    const int kVerifyCodeResentTime = 60;   //单位为秒
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    int loginSuccessful();

private slots:
    void on_loginButton_clicked();

    void on_pushButton_clicked();
    void on_updateVerfiyCodeReaminTime();
    void on_reqVerifyCodeButton_clicked();

private:
    void initUI();
    int startCalculateRemainTime(int ramainTime);
    Ui::LoginDialog *ui;
    bool bVerifyCodeValid_ = false;
    int remainTime_ = -1;                 //单位为秒
    QTimer *timer_ = nullptr;
};

#endif // LOGINDIALOG_H
