#include <QDateTime>

#include "triplistdialog.h"
#include "ui_triplistdialog.h"

void TripListDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    UserInfo *userInfo = UserInfo::getCurUserInfo();
    // 读取里程数
    float trip = userInfo->trip();
    float emissionReduction = trip * 0.12;  // 系数 0.12
    float consumeCalorie = trip * 54.539;     // 系数 54.539

    ui->tripLabel->setText(QString(u8"%1").arg(trip));
    ui->emissionReductionLabel->setText(QString(u8"%1").arg(emissionReduction));
    ui->consumeCalorieLabel->setText(QString(u8"%1").arg(consumeCalorie));
}

TripListDialog::TripListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TripListDialog)
{
    ui->setupUi(this);
    initTableWidget();


    initUI();
}

TripListDialog::~TripListDialog()
{
    delete ui;
}

void TripListDialog::initTableWidget()
{
    //设置列数和列宽
    int width;
    width = 3;
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setColumnWidth(0, width * 0.30);
    ui->tableWidget->setColumnWidth(1, width * 0.40);
    ui->tableWidget->setColumnWidth(2, width * 0.30);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << u8"日期" << u8"时间" << u8"金额";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setColumnWidth(0, 100);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidget->setRowCount(300);

    for (int i = 0; i < 100; i++) {
        ui->tableWidget->setRowHeight(i, 24);

        QTableWidgetItem *itemDate = new QTableWidgetItem(QDateTime::currentDateTime().toString("MM-dd"));
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("hh:mm") + QString(u8" %1分钟").arg(i + 1));
        QTableWidgetItem *itemRMB = new QTableWidgetItem(QString(u8"%1元").arg(i + 1));



        ui->tableWidget->setItem(i, 0, itemDate);
        ui->tableWidget->setItem(i, 1, itemTime);
        ui->tableWidget->setItem(i, 2, itemRMB);

    }
}
