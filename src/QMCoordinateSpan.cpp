/*****************************************************************************
 * QMCoordinateSpan.cpp
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

#include "QMCoordinateSpan.h"

QMCoordinateSpan::QMCoordinateSpan() : _latitudeDelta(0.0), _longitudeDelta(0.0)
{
}

QMCoordinateSpan::QMCoordinateSpan(qreal latitudeDelta, qreal longitudeDelta) :
    _latitudeDelta(latitudeDelta), _longitudeDelta(longitudeDelta)
{
}

qreal QMCoordinateSpan::latitudeDelta() const
{
    return _latitudeDelta;
}

void QMCoordinateSpan::setLatitudeDelta(qreal latitudeDelta)
{
    _latitudeDelta = latitudeDelta;
}

qreal QMCoordinateSpan::longitudeDelta() const
{
    return _longitudeDelta;
}

void QMCoordinateSpan::setLongitudeDelta(qreal longitudeDelta)
{
    _longitudeDelta = longitudeDelta;
}

bool QMCoordinateSpan::operator==(const QMCoordinateSpan &other)
{
    return (latitudeDelta() == other.latitudeDelta())
           && (longitudeDelta() == other.longitudeDelta());
}
