/*****************************************************************************
 * QMCoordinate.h
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

#ifndef QMCOORDINATE_H
#define QMCOORDINATE_H

#include <QtCore/QtGlobal>

// TODO: Add documentation to specify lat/lng ranges.
//       Latitude is in [-90, 90], and longitude is in [-180, 180]

class QMCoordinate
{
public:
    QMCoordinate();
    QMCoordinate(qreal latitude, qreal longitude);
    qreal latitude() const;
    qreal longitude() const;
    void setLatitude(qreal latitude);
    void setLongitude(qreal longitude);

    bool operator==(const QMCoordinate &other);

private:
    qreal _latitude;
    qreal _longitude;
};

#endif // QMCOORDINATE_H
