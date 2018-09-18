#include "homewindow.h"
#include <QApplication>
#include <QZXing.h>
#include <QDebug>

int main2()
{
    QImage imageToDecode("E:\\dn_class\\linux\\src\\mobike\\build-QZxing-Desktop_Qt_5_10_1_MSVC2015_32bit-Debug\\IMG_00000006.jpg");
    QZXing decoder;
    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 );
    qDebug()  << "imageToDecode:" << imageToDecode.width();
    QString result = decoder.decodeImage(imageToDecode);
    qDebug()  << "result:" << result;
    return 0;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeWindow w;
    w.show();

    return a.exec();
}
