#include <QMessageBox>
#include <QCameraInfo>
#include <QTimer>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QThread>
#include <QMessageBox>

#include <iostream>
#include <algorithm>
#include <future>
#include <numeric>


#include "scanqrcodedialog.h"
#include "ui_scanqrcodedialog.h"
#include <QZXing.h>
#include "worker.h"
#include "unlockdialog.h"
/**
 * 先使用定时器的方式去触发
 */
ScanQRCodeDialog::ScanQRCodeDialog(QWidget *parent) :
    QDialog(parent),decThread_(nullptr),
    ui(new Ui::ScanQRCodeDialog)
{
    ui->setupUi(this);
    initUI();

    setCamera();

}

ScanQRCodeDialog::~ScanQRCodeDialog()
{
    if(timer_)
    {
        timer_->stop();
        delete timer_;
        timer_ = nullptr;
    }
    delete ui;
    imageCapture->cancelCapture();
    delete imageCapture;
    camera->stop();
    delete camera;

    if(decThread_)
    {
        decThread_->stop();
        decThread_->quit();
        decThread_->wait();
        delete decThread_;
        decThread_ = nullptr;
    }
}

void ScanQRCodeDialog::setCamera(void)
{
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();

    camera = new QCamera();
    imageCapture=new QCameraImageCapture(camera);

    connect(imageCapture, &QCameraImageCapture::imageCaptured, this, &ScanQRCodeDialog::processCapturedImage);

    connect(this, SIGNAL(sigDisplayMode(int)), this, SLOT(changeDisplayMode(int)));
    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->setViewfinder(ui->viewfinder);
    camera->start();

    displayViewfinder();

    startScan(100);     // 开始扫描二维码
}

int ScanQRCodeDialog::captureImage()
{
//    qDebug() << "captureImage bScanFinish " << bScanFinish;
    if(!bScanFinish)
    {
        return imageCapture->capture();
    }
    else
    {
        timer_->stop();
    }
}

void ScanQRCodeDialog::displayViewfinder()
{
    qDebug() << "displayViewfinder";
    ui->stackedWidget->setCurrentIndex(0);
}

void ScanQRCodeDialog::displayCapturedImage()
{
    qDebug() << "displayCapturedImage";
    ui->stackedWidget->setCurrentIndex(1);
}

void ScanQRCodeDialog::changeDisplayMode(int mode)
{
    if(mode == 0)
    {
        displayViewfinder();
    }
    else if(mode == 1)
    {
        displayCapturedImage();
    }
    else if(mode == 2)
    {
        displayCapturedImage();

        if(pUnlockDialog_)
        {
            pUnlockDialog_->show();
            return;
        }
        pUnlockDialog_ = new UnlockDialog(this);
        pUnlockDialog_->setBikeInfo(qrCodeString_);
        int resutl = pUnlockDialog_ ->exec();
        if (resutl == QDialog::Accepted)
        {
            qDebug() << __FUNCTION__ << " You Choose Ok";
            // 开锁
            // 转到显示里程
            // 关闭当前对话框
            done(QDialog::Accepted);
            close();
        }
        else
        {
            qDebug() << __FUNCTION__ << " You Choose Cancel";
            // 重新扫描
            displayViewfinder();
            startScan(100);
        }
        delete pUnlockDialog_;
        pUnlockDialog_ = nullptr;
    }
}

void ScanQRCodeDialog::startScan(int msec)
{
    bScanFinish = false;
    if(!timer_)
    {
        timer_ = new QTimer();
    }
    else
    {
        timer_->stop();
    }
    if(decThread_)
    {
        decThread_->stop();
        decThread_->quit();
        decThread_->wait();
        delete decThread_;
        decThread_ = nullptr;
    }
    decThread_ = new QRCodeDecodeThread();
    decThread_->start();

    timer_->setInterval(msec);
    connect(timer_, SIGNAL(timeout()), this, SLOT(captureImage()));
    timer_->start(100);        // 开始触发
}


void ScanQRCodeDialog::displayImage(int , QImage image)
{
    //    ui->label_Display->setPixmap(QPixmap::fromImage(image));
    //    ui->statusBar->showMessage(tr("捕获成功"), 5000);
}

void ScanQRCodeDialog::saveImage()
{
    //    QString fileName=QFileDialog::getSaveFileName(this, tr("保存到文件"), QDir::homePath(), tr("jpeg格式文件(*.jpg)"));
    //    if(fileName.isEmpty()) {
    ////        ui->statusBar->showMessage(tr("保存操作已取消"), 5000);
    //        return;
    //    }
    //    const QPixmap* pixmap=ui->label_Display->pixmap();
    //    if(pixmap) {
    //        pixmap->save(fileName);
    ////        ui->statusBar->showMessage(tr("保存成功"), 5000);
    //    }
}

void ScanQRCodeDialog::on_captureButton_clicked()
{
    imageCapture->capture();
}

int asyncrocessCapturedImageExt(ScanQRCodeDialog *scan, const QImage& img)
{
    scan->asyncrocessCapturedImage(img);
    return 0;
}

void ScanQRCodeDialog::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);

    if(decThread_->getDecodeStatus() == QRCodeDecodeThread::kDecFinish)
    {
        if(decThread_->getDecodeResult().isEmpty())
        {
            decThread_->setImage(img);
        }
        else
        {
            qrCodeString_ = decThread_->getDecodeResult();
            bScanFinish = true;
            qDebug()  << "qrCodeString_:" << qrCodeString_;
            // 发送信号
            emit sigDisplayMode(2);
        }
    }

    timeUtil2_.reset();

}

//void ScanQRCodeDialog::processCapturedImage(int requestId, const QImage& img)
//{
//    Q_UNUSED(requestId);

//    // QFuture<void> future = QtConcurrent::run(&ScanQRCodeDialog::asyncrocessCapturedImage,this);
//    //QTimer::singleShot(0,pWork,SLOT(recogniseQRCode(const QImage&)));
//    qDebug() << "processCapturedImage" << "w = " << img.width() << ", h = " << img.height();
//     timeUtil_.reset();

//     image_ = img;
//    std::future<int> f1 = std::async(std::launch::async, asyncrocessCapturedImageExt, this, image_);
//     qDebug()  << "asyncrocessCapturedImageExt time:" << timeUtil_.elapsed();
//     qDebug()  << "processCapturedImage time:" << timeUtil2_.elapsed();

//    timeUtil2_.reset();

//}

void ScanQRCodeDialog::initUI()
{
    // 关闭对话框的问号“？”
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);

    ui->captureButton->hide();
}

void ScanQRCodeDialog::asyncrocessCapturedImage(const QImage& img)
{

    qDebug() << "w = " << img.width() << ", h = " << img.height();
    QImage scaledImage = img.scaled(ui->viewfinder->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    QZXing decoder;
    decoder.setDecoder( QZXing::DecoderFormat_QR_CODE | QZXing::DecoderFormat_EAN_13 );
    //timeUtil_.reset();

    qrCodeString_ = decoder.decodeImage(img);
    //qDebug()  << "decodeImage time:" << timeUtil_.elapsed();
    if(qrCodeString_.isEmpty())
    {
        // displayViewfinder();
        qDebug()  << "result failed ...";
    }
    else
    {

        qDebug()  << "result:" << qrCodeString_;
        bScanFinish = true;
        // 发送信号
        emit sigDisplayMode(2);
    }
}

void ScanQRCodeDialog::closeEvent(QCloseEvent *event)
{
    qDebug()  << "closeEvent:";
    //this->destroy(true);
    // this->close();
}
