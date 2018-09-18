#include "moneydialog.h"
#include "ui_moneydialog.h"
#include "ui_style_sheet.h"
#include "userinfo.h"
#include "rechargedialog.h"     // 充值
MoneyDialog::MoneyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoneyDialog)
{
    ui->setupUi(this);
    initUI();
}

MoneyDialog::~MoneyDialog()
{
    delete ui;
}

void MoneyDialog::updateRemainderInfo()
{
    UserInfo *userInfo = UserInfo::getCurUserInfo();
    float remainder = userInfo->remainder();
    ui->remainderButton->setText(QString(u8"%1元").arg(remainder));
}

void MoneyDialog::on_remainderButton_clicked()
{
    RechargeDialog *rechargeDialog = new RechargeDialog(this);
    int result = rechargeDialog->exec();

    updateRemainderInfo();
}

void MoneyDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    // 加载月卡宣传
    ui->monthCardButton->setStyleSheet(sheet_cost_monthCardButton);

    ui->remainderButton->setStyleSheet(sheet_remainderButton);
    ui->redPacketButton->setStyleSheet(sheet_remainderButton);

    // 更新余额
    updateRemainderInfo();
}
