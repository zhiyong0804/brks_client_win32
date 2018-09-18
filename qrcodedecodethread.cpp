#include "qrcodedecodethread.h"

QRCodeDecodeThread::QRCodeDecodeThread():
    decStatus_(kDecFinish)
{
    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 );
}

QRCodeDecodeThread::EDecStatus QRCodeDecodeThread::getDecodeStatus()
{
    EDecStatus decStatus;
    mutex_.lock();
    decStatus = decStatus_;
    mutex_.unlock();
    return decStatus;
}

void QRCodeDecodeThread::setDecodeStatus(QRCodeDecodeThread::EDecStatus decStatus)
{
    mutex_.lock();
    decStatus_  = decStatus;
    mutex_.unlock();
}

int QRCodeDecodeThread::setImage(const QImage image)
{
    EDecStatus decStatus = getDecodeStatus();

    if(decStatus != kDecFinish )
    {
        return -1;
    }
    image_ = image;
    setDecodeStatus(kDecReady);
    return 0;
}

QString QRCodeDecodeThread::getDecodeResult()
{
    QString result;
    mutex_.lock();
    result  = decResult_;
    mutex_.unlock();

    return result;
}

void QRCodeDecodeThread::run()
{
    EDecStatus decStatus = getDecodeStatus();

    while(!stopped)
    {
        decStatus = getDecodeStatus();
        if(decStatus == kDecReady)
        {
            setDecodeStatus(kDeccoding);
            // 开始解码
            decResult_ = decoder.decodeImage(image_);
            // 解码完毕
            setDecodeStatus(kDecFinish);
        }
        else
        {
            msleep(30);
        }
    }

}
