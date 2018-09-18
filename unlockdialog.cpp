#include <QTimer>
#include "unlockdialog.h"
#include "ui_unlockdialog.h"

UnlockDialog::UnlockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnlockDialog)
{
    ui->setupUi(this);
    initUI();
}

UnlockDialog::~UnlockDialog()
{
    delete ui;
}

void UnlockDialog::setBikeInfo(QString bikeInfo)
{
    bikeInfo_ = bikeInfo;

    ui->bikeInfoLabel->setText(bikeInfo_);
}

void UnlockDialog::unlockFinish()
{
    ui->circularWidget->hide();
    bikeInfo_ = tr("Unlock OK");
    //ui->bikeInfoLabel->setText(bikeInfo_);
    QImage *image = new QImage("home_unlock_to_success_32.png");
    ui->bikeInfoLabel->setPixmap(QPixmap::fromImage(*image));
    //ui->bikeInfoLabel->setText(QApplication::translate("UnlockDialog", "\350\247\243\351\224\201\346\210\220\345\212\237", nullptr));
    ui->bikeInfoLabel->show();
    ui->tipLabel->setText(QApplication::translate("UnlockDialog", "\350\247\243\351\224\201\346\210\220\345\212\237", nullptr));
    QTimer::singleShot(2000, this, &UnlockDialog::unlockExit);

}

void UnlockDialog::unlockExit()
{
    // 关闭对话框
    close();
    done(Accepted);
}

void UnlockDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    // 先隐藏刷新
    ui->circularWidget->hide();
    ui->tipLabel->hide();
}


void UnlockDialog::on_cancelButton_clicked()
{
    // 关闭对话框
    close();
    done(Rejected);
}

void UnlockDialog::on_unlockButton_clicked()
{
    ui->bikeInfoLabel->hide();
    ui->circularWidget->setLineWidth(15);
    ui->circularWidget->setSize(120);
    ui->circularWidget->setColor(QColor(0, 0, 255));
    ui->circularWidget->show();

    ui->tipLabel->show();
    QTimer::singleShot(3000, this, &UnlockDialog::unlockFinish);
}
