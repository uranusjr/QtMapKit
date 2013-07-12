/*****************************************************************************
 * Widget.h
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

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include <QMMapView.h>
#include <QMCoordinateRegion.h>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void log(QString text, QString delimiter = QString("\n"));
    void log(const char *text, QString delimiter = QString("\n"));

private slots:
    void onMapLoaded();
    void onMapBecameIdle();
    void onRegionChanged(QMCoordinateRegion region);

private:
    QMMapView *_mapView;
    QWidget *_controls;
    QTextEdit *_logger;
    void buildControls();
};

#endif // WIDGET_H
