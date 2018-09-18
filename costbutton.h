#ifndef COSTBUTTON_H
#define COSTBUTTON_H
#include <QPushButton>

class CostButton : public QPushButton
{
    Q_OBJECT
public:
    CostButton(QWidget *parent = 0);
    void select(bool select);
//private:

};

#endif // COSTBUTTON_H
