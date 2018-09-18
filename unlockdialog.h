#ifndef UNLOCKDIALOG_H
#define UNLOCKDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class UnlockDialog;
}

class UnlockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UnlockDialog(QWidget *parent = 0);
    ~UnlockDialog();
    void setBikeInfo(QString bikeInfo);
private:
    void unlockFinish();
    void unlockExit();
    void initUI();
private slots:
    void on_cancelButton_clicked();

    void on_unlockButton_clicked();

private:
    Ui::UnlockDialog *ui;
    QString bikeInfo_;
};

#endif // UNLOCKDIALOG_H
