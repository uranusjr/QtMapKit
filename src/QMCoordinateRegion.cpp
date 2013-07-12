/*****************************************************************************
 * QMCoordinateRegion.cpp
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

#include "QMCoordinateRegion.h"
#include <QtDebug>

QMCoordinateRegion::QMCoordinateRegion() :
    _east(0.0), _west(0.0), _north(0.0), _south(0.0)
{
}

QMCoordinateRegion::QMCoordinateRegion(QMCoordinate southWest,
                                       QMCoordinate northEast) :
    _east(northEast.longitude()),
    _west(southWest.longitude()),
    _north(northEast.latitude()),
    _south(southWest.latitude())
{
}

QMCoordinateRegion::QMCoordinateRegion(qreal north, qreal south,
                                       qreal east, qreal west) :
    _east(east), _west(west), _north(north), _south(south)
{
}

QMCoordinateRegion::QMCoordinateRegion(QMCoordinate center,
                                       QMCoordinateSpan span) :
    _east(center.longitude() + span.longitudeDelta() / 2),
    _west(center.longitude() - span.longitudeDelta() / 2),
    _north(center.latitude() + span.latitudeDelta() / 2),
    _south(center.latitude() - span.latitudeDelta() / 2)
{
}

bool QMCoordinateRegion::contains(QMCoordinate &point, bool proper) const
{
    qreal lng = point.longitude();
    qreal lat = point.latitude();

    bool r = false;
    if (proper)
        r = lat > west() && lat < east() && lng > south() && lng < north();
    else
        r = lat >= west() && lat <= east() && lng >= south() && lng <= north();

    return r;
}

bool QMCoordinateRegion::intersects(QMCoordinateRegion &span) const
{
    Q_UNUSED(span)
    qWarning("QMCoordinateRegion::intersects not implemented; false returned");
    return false;
}

bool QMCoordinateRegion::isEmpty() const
{
    return (east() == west()) || (north() == south());
}

qreal QMCoordinateRegion::east() const
{
    return _east;
}

qreal QMCoordinateRegion::west() const
{
    return _west;
}

qreal QMCoordinateRegion::north() const
{
    return _north;
}

qreal QMCoordinateRegion::south() const
{
    return _south;
}

void QMCoordinateRegion::setEast(qreal value)
{
    _east = value;
}

void QMCoordinateRegion::setWest(qreal value)
{
    _west = value;
}

void QMCoordinateRegion::setNorth(qreal value)
{
    _north = value;
}

void QMCoordinateRegion::setSouth(qreal value)
{
    _south = value;
}

QMCoordinate QMCoordinateRegion::southWest() const
{
    return QMCoordinate(south(), west());
}

QMCoordinate QMCoordinateRegion::northEast() const
{
    return QMCoordinate(north(), east());
}

QMCoordinate QMCoordinateRegion::southEast() const
{
    return QMCoordinate(south(), east());
}

QMCoordinate QMCoordinateRegion::northWest() const
{
    return QMCoordinate(north(), west());
}

QMCoordinate QMCoordinateRegion::center() const
{
    return QMCoordinate((north() + south()) / 2, (east() + west()) / 2);
}

QMCoordinateSpan QMCoordinateRegion::span() const
{
    return QMCoordinateSpan(north() - south(), east() - west());
}

bool QMCoordinateRegion::operator ==(const QMCoordinateRegion &other)
{
    return (east() == other.east())
            && (west() == other.west())
            && (north() == other.north())
            && (south() == other.south());
}
