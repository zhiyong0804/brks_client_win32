#ifndef MONEYDIALOG_H
#define MONEYDIALOG_H

#include <QDialog>

namespace Ui {
class MoneyDialog;
}

class MoneyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MoneyDialog(QWidget *parent = 0);
    ~MoneyDialog();

private slots:
    void on_remainderButton_clicked();

private:
    void initUI();
    Ui::MoneyDialog *ui;
    void updateRemainderInfo();
};

#endif // MONEYDIALOG_H
