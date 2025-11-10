QT -= gui
QT += network

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = oplinkB-tcpbackend
BUNDLE_NAME_QT = $${BUNDLE_NAME}-qt6
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}

SOURCES += \
    tcpbackendplugin.cpp

HEADERS += \
    tcpbackendplugin.h

# meta file name for this bundle
DISTFILES += ../$${BUNDLE_NAME}bundle.json

# include dir for compilation
INCLUDEPATH += \
        ../lib \
        ../../../core-lib \
        ../../../core-backend-lib \
        ../../../../../plugframe/core-lib

LIBS    +=  -l$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}.a
