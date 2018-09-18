#include "bikemapview.h"
#include <QWebChannel>
#include <QDir>
#include <QString>
#include <QDebug>
BikeMapView::BikeMapView(QWidget* parent)
    :QWebEngineView(parent)
{

    QDir temDir("bikemap/Baidu_JS/bikemap.html");
    // "E:/dn_class/linux/src/mobike/mobike/bikemap/bikeBaidu_JS/bikemap.html"
    // E:\dn_class\linux\src\mobike\mobike\bikemap\Baidu_JS
    QString absDir = temDir.absolutePath();

    qDebug() << absDir;
    QWebChannel *channel = new QWebChannel(this);
  //  channel->registerObject("bridge", (QObject*)bridge::instance());
    this->page()->setWebChannel(channel);
    this->page()->load(QUrl(QString("file:///%0").arg(absDir)));
}
