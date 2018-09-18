#ifndef QRCODECAMERAVIEWFINDER_H
#define QRCODECAMERAVIEWFINDER_H
#include <QCameraViewfinder>
#include <QPaintEvent>
#include <QWidget>

class QRCodeCameraViewfinder : public QCameraViewfinder
{
    Q_OBJECT
public:
    explicit QRCodeCameraViewfinder(QWidget *parent = Q_NULLPTR);
protected:
    virtual void paintEvent(QPaintEvent *);
};

#endif // QRCODECAMERAVIEWFINDER_H
