/*****************************************************************************
 * QMMapView.h
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

#ifndef QMMAPVIEW_H
#define QMMAPVIEW_H

#include <QWidget>
#include "QtMapKit.h"
#include "QMCoordinate.h"
#include "QMCoordinateRegion.h"
class QMMapViewPrivate;

class QMMapView : public QWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QMMapView)

public:
    enum MapType {
        Hybrid,
        RoadMap,
        Satellite,
        Terrain
    };

    QMMapView(MapType mapType, QMCoordinate center, uint zoomLevel,
              QWidget *parent = 0);
    MapType mapType() const;

    QMCoordinateRegion region() const;
    QMCoordinate center() const;

    uint zoomLevel() const;
    qreal heading() const;
    qreal tilt() const;

    void setMapType(MapType type);

    void setCenter(QMCoordinate center, bool animated = true);
    void setZoomLevel(uint zoom);

    void makeRegionVisible(QMCoordinateRegion &region);
    void fitRegion(QMCoordinateRegion &region);
//    void pan(int x, int y);
//    void setHeading(qreal heading);
//    void setTilt(qreal tile);

//    ??? projection() const; get
//    ??? streetView() const; get set
//    QUrl draggableCursor(); get set
//    QUrl draggingCursor(); get set
//    bool useMapMarker() const; get set

protected:
    void resizeEvent(QResizeEvent *);

signals:
    void mapLoaded();
    void mapBecameIdle();
    void regionChanged(QMCoordinateRegion region);
    void centerChanged(QMCoordinate center);
    void mouseClicked(QMCoordinate coordinate);
    void mouseDoubleClicked(QMCoordinate coordinate);
    void mouseRightClicked(QMCoordinate coordinate);
    void mouseDragged();
    void mouseDragStarted();
    void mouseDragEnded();
    void cursorMoved(QMCoordinate coordinate);
    void cursorEntered(QMCoordinate coordinate);
    void cursorLeaved(QMCoordinate coordinate);
    void headingChanged();
    void mapTypeChanged(MapType type);
//    void projectionChanged();
    void tilesLoaded();
    void tilesChanged();
    void zoomLevelChanged(uint level);

protected slots:
    void initializeMap();
    void insertNativeObject();
    void regionDidChangeTo(qreal north, qreal south, qreal east, qreal west);
    void centerDidChangeTo(qreal latitude, qreal longitude);
    void mapTypeDidChangeTo(QString typeString);
    void mouseDidClickAt(qreal latitude, qreal longitude);
    void mouseDidDoubleClickAt(qreal latitude, qreal longitude);
    void mouseDidRightClickAt(qreal latitude, qreal longitude);
    void cursorDidMoveTo(qreal latitude, qreal longitude);
    void cursorDidEnterTo(qreal latitude, qreal longitude);
    void cursorDidLeaveFrom(qreal latitude, qreal longitude);

private:
    QMMapViewPrivate *d_ptr;
};

#endif // QMMAPVIEW_H
