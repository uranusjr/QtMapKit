/*****************************************************************************
 * QMCoordinateSpan.h
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

#ifndef QMCOORDINATESPAN_H
#define QMCOORDINATESPAN_H

#include <QtCore/QtGlobal>

class QMCoordinateSpan
{
public:
    QMCoordinateSpan();
    QMCoordinateSpan(qreal latitudeDelta, qreal longitudeDelta);
    qreal latitudeDelta() const;
    qreal longitudeDelta() const;
    void setLatitudeDelta(qreal latitudeDelta);
    void setLongitudeDelta(qreal longitudeDelta);

    bool operator==(const QMCoordinateSpan &other);

private:
    qreal _latitudeDelta;
    qreal _longitudeDelta;
};

#endif // QMCOORDINATESPAN_H
