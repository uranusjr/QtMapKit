/*****************************************************************************
 * QMMapView.cpp
 *
 * Created: 08/7 2013 by uranusjr
 *
 * Copyright 2013 uranusjr. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#include "QMMapView.h"
#include <QHBoxLayout>
#include <QHash>
#include <QVariantMap>
#include <QWebFrame>
#include <QWebView>
#include <QtDebug>

class CustomWebPage : public QWebPage
{
    public:
        CustomWebPage(QObject *parent = 0) : QWebPage(parent) {}

    protected:
        virtual void javaScriptConsoleMessage(
                const QString &message, int lineNumber,
                const QString &sourceID);
};

void CustomWebPage::javaScriptConsoleMessage(
        const QString &message, int lineNumber, const QString &sourceID)
{
    qDebug() << "JavaScript" << sourceID << "line" << lineNumber <<
                ":" << message;
}


class QMMapViewPrivate
{
    Q_DECLARE_PUBLIC(QMMapView)

public:
    QMMapViewPrivate(QMMapView *q) : q_ptr(q), loaded(false)
    {
        webView = new QWebView();
        webView->setPage(new CustomWebPage());
        webView->load(QUrl("qrc:///qtmapkit/gmap/gmap.html"));
    }
    ~QMMapViewPrivate() {}
    QMMapView *q_ptr;

    bool loaded;
    QWebView *webView;
    struct {
        QMCoordinate centerCoordinate;
        QMMapView::MapType mapType;
        uint zoomLevel;
    } initialValues;

    inline QWebFrame *frame() { return webView->page()->mainFrame(); }
    inline QVariant evaluateJavaScript(const QString &script,
                                       bool force = false)
    {
        if (loaded || force)
            return frame()->evaluateJavaScript(script);
        else
            return QVariant();
    }
    inline QString toJsMapType(QMMapView::MapType type)
    {
        QString typeName;
        switch (type)
        {
        case QMMapView::Hybrid:
            typeName = "HYBRID";
            break;
        case QMMapView::RoadMap:
            typeName = "ROADMAP";
            break;
        case QMMapView::Satellite:
            typeName = "SATELLITE";
            break;
        case QMMapView::Terrain:
            typeName = "TERRAIN";
            break;
        }
        return QString("google.maps.MapTypeId.%1").arg(typeName);
    }
    inline QMMapView::MapType fromJsMapType(QString &type)
    {
        static QHash<QString, QMMapView::MapType> types;
        if (types.isEmpty())
        {
            types.insert("hybrid", QMMapView::Hybrid);
            types.insert("roadmap", QMMapView::RoadMap);
            types.insert("satellite", QMMapView::Satellite);
            types.insert("terrain", QMMapView::Terrain);
        }
        return types.value(type, initialValues.mapType);
    }
};

QMMapView::QMMapView(MapType mapType, QMCoordinate center, uint zoomLevel,
                     QWidget *parent) :
    QWidget(parent), d_ptr(new QMMapViewPrivate(this))
{
    Q_D(QMMapView);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(d->webView);
    setLayout(mainLayout);

    d->initialValues.centerCoordinate = center;
    d->initialValues.mapType = mapType;
    d->initialValues.zoomLevel = zoomLevel;
    connect(d->frame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(insertNativeObject()));
    connect(d->webView, SIGNAL(loadFinished(bool)),
            this, SLOT(initializeMap()));
}

void QMMapView::insertNativeObject()
{
    Q_D(QMMapView);
    d->frame()->addToJavaScriptWindowObject("qMapView", this);
}

void QMMapView::initializeMap()
{
    Q_D(QMMapView);
    if (d->loaded)
        return;
    QMCoordinate &center = d->initialValues.centerCoordinate;
    QString js = QString("initialize(%1, %2, %3, %4);").arg(
                QString::number(center.longitude()),
                QString::number(center.latitude()),
                d->toJsMapType(d->initialValues.mapType),
                QString::number(d->initialValues.zoomLevel));
    d->evaluateJavaScript(js, true);

    d->loaded = true;
    emit mapLoaded();
}

void QMMapView::resizeEvent(QResizeEvent *)
{
    Q_D(QMMapView);
    d->evaluateJavaScript("google.maps.event.trigger(map, 'resize');");
}

QMMapView::MapType QMMapView::mapType() const
{
    QString res = d_ptr->evaluateJavaScript("map.getMapTypeId();").toString();
    return d_ptr->fromJsMapType(res);
}

/** Returns the map's current visible region.
 * Corresponds to `getBounds()`. Due to the limitation in the Google Map
 * JavaScript API, this method works only after the first `regionChanged()`
 * signal is sent. The result of any invocation of this method before that is
 * undifined.
 */
QMCoordinateRegion QMMapView::region() const
{
    QVariantMap result = d_ptr->evaluateJavaScript("getMapBounds();").toMap();
    return QMCoordinateRegion(QMCoordinate(result["south"].toReal(),
                                           result["west"].toReal()),
                              QMCoordinate(result["north"].toReal(),
                                           result["east"].toReal()));
}

QMCoordinate QMMapView::center() const
{
    QVariantMap result = d_ptr->evaluateJavaScript("getMapCenter();").toMap();
    return QMCoordinate(result["latitude"].toReal(),
                        result["longitude"].toReal());
}

uint QMMapView::zoomLevel() const
{
    return d_ptr->evaluateJavaScript("map.getZoom();").toUInt();
}

qreal QMMapView::heading() const
{
    return d_ptr->evaluateJavaScript("map.getHeading();").toReal();
}

qreal QMMapView::tilt() const
{
    return d_ptr->evaluateJavaScript("map.getTilt();").toReal();
}

void QMMapView::setMapType(MapType type)
{
    Q_D(QMMapView);
    QString typeName = d->toJsMapType(type);
    QString script = QString("map.setMapTypeId(%1);").arg(typeName);
    d->evaluateJavaScript(script);
}

void QMMapView::setCenter(QMCoordinate center, bool animated)
{
    Q_D(QMMapView);
    QString format = QString("setMapCenter(%1, %2, %3);");
    QString js = format.arg(QString::number(center.latitude()),
                            QString::number(center.longitude()),
                            animated ? "true" : "false");
    d->evaluateJavaScript(js);
}

void QMMapView::setZoomLevel(uint zoom)
{
    Q_D(QMMapView);
    d->evaluateJavaScript(QString("map.setZoom(%1);").arg(zoom));
}

void QMMapView::makeRegionVisible(QMCoordinateRegion &region)
{
    Q_D(QMMapView);
    QString format = QString("panMapToBounds(%1, %2, %3, %4);");
    QString js = format
            .arg(region.north())
            .arg(region.south())
            .arg(region.east())
            .arg(region.west());
    d->evaluateJavaScript(js);
}

void QMMapView::fitRegion(QMCoordinateRegion &region)
{
    Q_D(QMMapView);
    QString format = QString("fitMapToBounds(%1, %2, %3, %4);");
    QString js = format
            .arg(region.north())
            .arg(region.south())
            .arg(region.east())
            .arg(region.west());
    d->evaluateJavaScript(js);
}

void QMMapView::regionDidChangeTo(qreal north, qreal south,
                                  qreal east, qreal west)
{
    emit regionChanged(QMCoordinateRegion(north, south, east, west));
}

void QMMapView::centerDidChangeTo(qreal latitude, qreal longitude)
{
    emit centerChanged(QMCoordinate(latitude, longitude));
}

void QMMapView::mapTypeDidChangeTo(QString typeString)
{
    Q_D(QMMapView);
    emit mapTypeChanged(d->fromJsMapType(typeString));
}

void QMMapView::mouseDidClickAt(qreal latitude, qreal longitude)
{
    emit mouseClicked(QMCoordinate(latitude, longitude));
}

void QMMapView::mouseDidDoubleClickAt(qreal latitude, qreal longitude)
{
    emit mouseDoubleClicked(QMCoordinate(latitude, longitude));
}

void QMMapView::mouseDidRightClickAt(qreal latitude, qreal longitude)
{
    emit mouseRightClicked(QMCoordinate(latitude, longitude));
}

void QMMapView::cursorDidMoveTo(qreal latitude, qreal longitude)
{
    emit cursorMoved(QMCoordinate(latitude, longitude));
}

void QMMapView::cursorDidEnterTo(qreal latitude, qreal longitude)
{
    emit cursorEntered(QMCoordinate(latitude, longitude));
}

void QMMapView::cursorDidLeaveFrom(qreal latitude, qreal longitude)
{
    emit cursorLeaved(QMCoordinate(latitude, longitude));
}
