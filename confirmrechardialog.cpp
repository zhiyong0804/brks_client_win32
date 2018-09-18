#include "confirmrechardialog.h"
#include "ui_confirmrechardialog.h"
#include <QDebug>
#include "ui_style_sheet.h"
void ConfirmRecharDialog::initUI(const int cost)
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);//输入的时候就显示圆点

    ui->costLabel->setText(QString(u8"%1元").arg(cost));

    ui->rechargeButton->setStyleSheet(sheet_recharge_confirmButton);
}

ConfirmRecharDialog::ConfirmRecharDialog(const int cost, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfirmRecharDialog)
{
    ui->setupUi(this);

    initUI(cost);
}

ConfirmRecharDialog::~ConfirmRecharDialog()
{
    delete ui;
}

void ConfirmRecharDialog::on_rechargeButton_clicked()
{
    qDebug() << "ui->costLabel->text():" << ui->passwordLineEdit->text();
    if(!ui->passwordLineEdit->text().isEmpty())
    {
        done(QDialog::Accepted);
        close();
    }
}
