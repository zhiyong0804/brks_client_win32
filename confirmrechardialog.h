#ifndef CONFIRMRECHARDIALOG_H
#define CONFIRMRECHARDIALOG_H

#include <QDialog>

namespace Ui {
class ConfirmRecharDialog;
}

class ConfirmRecharDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmRecharDialog(const int cost, QWidget *parent = 0);
    ~ConfirmRecharDialog();

private slots:
    void on_rechargeButton_clicked();

private:
    Ui::ConfirmRecharDialog *ui;
    void initUI(const int cost);
};

#endif // CONFIRMRECHARDIALOG_H
