#ifndef WORKER_H
#define WORKER_H
#include <QObject>
class QImage;
class ScanQRCodeDialog;
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker();
    void setScanQRCodeDialogHandle(ScanQRCodeDialog *handle);
    ~Worker();
signals:

public slots:
    void recogniseQRCode(const QImage& img);
private:
    QObject parent_;
    ScanQRCodeDialog *handle_;
};

#endif // WORKER_H
