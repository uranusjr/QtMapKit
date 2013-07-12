#-------------------------------------------------
#
# Project created by QtCreator 2013-07-08T08:47:20
#
#-------------------------------------------------

QT       += webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = qtmapkit
TEMPLATE = lib

DEFINES += QTMAPKIT_LIBRARY

DESTDIR = ../lib
OBJECTS_DIR = ../build
MOC_DIR = ../build
RCC_DIR = ../build
UI_DIR = ../build

SOURCES += \
    QMMapView.cpp \
    QMCoordinate.cpp \
    QMCoordinateRegion.cpp \
    QMCoordinateSpan.cpp

HEADERS += QtMapKit.h\
    qtmapkit_global.h \
    QMMapView.h \
    QMCoordinate.h \
    QMCoordinateRegion.h \
    QMCoordinateSpan.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    qtmapkit_resources.qrc

OTHER_FILES += \
    gmap.html \
    gmap.js
