/*****************************************************************************
 * qtmapkit_global.h
 *
 * Created: 08/7 2013 by uranusjr
 *
 * Copyright 2013 uranusjr. All rights reserved.
 *
 * This file is published under the Creative Commons 3.0.
 * http://creativecommons.org/licenses/by/3.0/
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/

#ifndef QTMAPKIT_GLOBAL_H
#define QTMAPKIT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTMAPKIT_LIBRARY)
#  define QTMAPKITSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTMAPKITSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTMAPKIT_GLOBAL_H
