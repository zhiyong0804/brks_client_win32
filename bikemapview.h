#ifndef BIKEMAPVIEW_H
#define BIKEMAPVIEW_H
#include <QWebEngineView>

class BikeMapView : public QWebEngineView
{
    Q_OBJECT
public:
    explicit BikeMapView(QWidget* parent = Q_NULLPTR);
};

#endif // BIKEMAPVIEW_H
