#include "worker.h"
#include "scanqrcodedialog.h"
Worker::Worker() : QObject()
{

}

void Worker::setScanQRCodeDialogHandle(ScanQRCodeDialog *handle)
{
    handle_ = handle;
}

Worker::~Worker()
{

}

void Worker::recogniseQRCode(const QImage &img)
{
    //ScanQRCodeDialog *scanQRcode = (ScanQRCodeDialog *)parent_;
    handle_->asyncrocessCapturedImage(img);
}
