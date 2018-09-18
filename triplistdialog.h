#ifndef TRIPLISTDIALOG_H
#define TRIPLISTDIALOG_H

#include <QDialog>
#include "userinfo.h"

namespace Ui {
class TripListDialog;
}

class TripListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TripListDialog(QWidget *parent = 0);
    ~TripListDialog();

    void initUI();

private:
    void initTableWidget();
    Ui::TripListDialog *ui;
};

#endif // TRIPLISTDIALOG_H
