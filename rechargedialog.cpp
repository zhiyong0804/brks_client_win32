#include "rechargedialog.h"
#include "ui_rechargedialog.h"
#include "userinfo.h"
#include "ui_style_sheet.h"
#include "confirmrechardialog.h"
void RechargeDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    // 余额图标
    ui->remainerButton->setStyleSheet(sheet_recharge_remainderButton);
    // 微信支付图标
    ui->weixinButton->setStyleSheet(sheet_recharge_weixinButton);
    // 更新支付宝图标
    ui->aliplayButton->setStyleSheet(sheet_recharge_aliplayButton);

    ui->rechargeButton->setStyleSheet(sheet_recharge_confirmButton);
    // 更新充值选择金额画面
    unSelectAllCost();


    // 更新余额
    UserInfo *userInfo = UserInfo::getCurUserInfo();
    float remainder = userInfo->remainder();
    ui->remainderLabel->setText(QString(u8"%1元").arg(remainder));

}

RechargeDialog::RechargeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechargeDialog)
{
    ui->setupUi(this);

    initUI();
}

RechargeDialog::~RechargeDialog()
{
    delete ui;
}

void RechargeDialog::unSelectAllCost()
{
    ui->cost100RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
    ui->cost50RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
    ui->cost20RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
    ui->cost10RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
    ui->cost5RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
    ui->cost1RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
}

void RechargeDialog::selectCost(int cost)
{
    // 先将原来的反选
    switch (cost_) {
    case 100:
        ui->cost100RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
        break;
    case 50:
        ui->cost50RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
        break;
    case 20:
        ui->cost20RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
        break;
    case 10:
        ui->cost10RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
        break;
    case 5:
        ui->cost5RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
        break;
    case 1:
        ui->cost1RmbButton->setStyleSheet(sheet_recharge_cost_unselect);
        break;
    default:
        break;
    }

    cost_ = cost;
    // 新选中
    switch (cost_) {
    case 100:
        ui->cost100RmbButton->setStyleSheet(sheet_recharge_cost_select);
        break;
    case 50:
        ui->cost50RmbButton->setStyleSheet(sheet_recharge_cost_select);
        break;
    case 20:
        ui->cost20RmbButton->setStyleSheet(sheet_recharge_cost_select);
        break;
    case 10:
        ui->cost10RmbButton->setStyleSheet(sheet_recharge_cost_select);
        break;
    case 5:
        ui->cost5RmbButton->setStyleSheet(sheet_recharge_cost_select);
        break;
    case 1:
        ui->cost1RmbButton->setStyleSheet(sheet_recharge_cost_select);
        break;
    default:
        break;
    }
}

void RechargeDialog::on_cost100RmbButton_clicked()
{
    selectCost(100);
}

void RechargeDialog::on_cost50RmbButton_clicked()
{
    selectCost(50);
}

void RechargeDialog::on_cost20RmbButton_clicked()
{
    selectCost(20);
}

void RechargeDialog::on_cost10RmbButton_clicked()
{
    selectCost(10);
}

void RechargeDialog::on_cost5RmbButton_clicked()
{
    selectCost(5);
}

void RechargeDialog::on_cost1RmbButton_clicked()
{
    selectCost(1);
}

void RechargeDialog::on_rechargeButton_clicked()
{
    if(ui->weixinRadio->isChecked() || ui->aliplayRadio->isChecked())
    {
        if(cost_ != 0)
        {
            ConfirmRecharDialog *confirDialog = new ConfirmRecharDialog(cost_, this);
            int result = confirDialog->exec();
            if(result == QDialog::Accepted)     // 充值成功则修改金额
            {
                // 充值
                UserInfo *userInfo = UserInfo::getCurUserInfo();
                float remainder = userInfo->remainder();
                remainder += cost_;
                userInfo->setRemainder(remainder);
                userInfo->sync();
                ui->remainderLabel->setText(QString(u8"%1元").arg(remainder));
            }
        }
    }
    else
    {

    }
}
