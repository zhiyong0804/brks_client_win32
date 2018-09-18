#ifndef RECHARGEDIALOG_H
#define RECHARGEDIALOG_H

#include <QDialog>

namespace Ui {
class RechargeDialog;
}

class RechargeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RechargeDialog(QWidget *parent = 0);
    ~RechargeDialog();

private slots:
    void on_cost100RmbButton_clicked();

    void on_cost50RmbButton_clicked();

    void on_cost20RmbButton_clicked();

    void on_cost10RmbButton_clicked();

    void on_cost5RmbButton_clicked();

    void on_cost1RmbButton_clicked();

    void on_rechargeButton_clicked();

private:
    void unSelectAllCost();
    void selectCost(int cost);
    Ui::RechargeDialog *ui;
    void initUI();
    int cost_ = 0;          // 记录当前充值金额的选择
};

#endif // RECHARGEDIALOG_H
