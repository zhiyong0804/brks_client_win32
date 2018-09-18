#ifndef USERDIALOG_H
#define USERDIALOG_H

#include <QDialog>
#include "userinfo.h"

namespace Ui {
class UserDialog;
}

class UserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDialog(QWidget *parent = 0);
    ~UserDialog();

private slots:
    void on_logOffButton_clicked();

    void on_tripButton_clicked();

    void on_remainderButton_clicked();

private:
    Ui::UserDialog *ui;
    void initUI();
    void updateUserInfo();
};

#endif // USERDIALOG_H
