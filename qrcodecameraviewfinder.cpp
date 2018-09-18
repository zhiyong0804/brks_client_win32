#include <QPainter>
#include "qrcodecameraviewfinder.h"

QRCodeCameraViewfinder::QRCodeCameraViewfinder(QWidget *parent):
    QCameraViewfinder(parent)
{

}

void QRCodeCameraViewfinder::paintEvent(QPaintEvent *e)
{
    QCameraViewfinder::paintEvent (e);
    QPainter painter(this);
    painter.setPen(Qt::gray);
    painter.drawRect(50, 15, 380, 270);     // 480 300

//    painter.setPen(Qt::red);
//    QPoint point1(60, 20);
//    QPoint point2(50+370, 20);
//    painter.drawLine(point1, point2);
}
