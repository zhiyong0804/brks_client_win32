#ifndef SCANQRCODEDIALOG_H
#define SCANQRCODEDIALOG_H

#include <QDialog>
#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsVideoItem>

#include "timerutil.h"
#include "thread.h"
#include "qrcodedecodethread.h"
class Worker;
class QThread;
class QTimer;
/**
 * 二维码扫描对话框
 *
 */

namespace Ui {
class ScanQRCodeDialog;
}

class UnlockDialog;

class ScanQRCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScanQRCodeDialog(QWidget *parent = 0);
    ~ScanQRCodeDialog();
    void setCamera(void);
    void displayViewfinder();


    void startScan(int msec);
    void asyncrocessCapturedImage(const QImage& img);
    void closeEvent(QCloseEvent *event);
    void displayCapturedImage();
private slots:
    void changeDisplayMode(int mode);
    int captureImage();
    void displayImage(int,QImage);
    void saveImage();
    void on_captureButton_clicked();
    void processCapturedImage(int requestId, const QImage &img);
signals:
    void sigDisplayMode(int);
private:
    void initUI(void);
    Ui::ScanQRCodeDialog *ui;
    QCamera *camera;
    QCameraImageCapture *imageCapture;
    bool exit_ = false;

    bool bScanFinish = false;
    QThread *pThread;
    Worker *pWork;
    QTimer *timer_ = nullptr;
    TimerUtil timeUtil_;
    TimerUtil timeUtil2_;
    QString qrCodeString_;

    // 另一种视图
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsVideoItem *videoItem ;
    UnlockDialog *pUnlockDialog_ = nullptr;
    QImage image_;

    QRCodeDecodeThread *decThread_;
};

#endif // SCANQRCODEDIALOG_H
