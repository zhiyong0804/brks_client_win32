#ifndef QRCODEDECODETHREAD_H
#define QRCODEDECODETHREAD_H
#include <QString>
#include <QMutex>
#include <QImage>
#include "thread.h"
#include <QZXing.h>

class QRCodeDecodeThread : public Thread
{
    Q_OBJECT
public:
    typedef enum eDecStatus{
        kDecReady,
        kDeccoding,
        kDecFinish,
    }EDecStatus;
public:
    QRCodeDecodeThread();
    EDecStatus getDecodeStatus();
   inline void setDecodeStatus(EDecStatus decStatus);
    int setImage(const QImage image);
    QString getDecodeResult();
    void run();

private:
    EDecStatus decStatus_;
    QString decResult_;
    QMutex mutex_;
    QImage image_;
    QZXing decoder;
};

#endif // QRCODEDECODETHREAD_H
