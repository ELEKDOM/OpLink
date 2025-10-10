QT -= gui
QT += network

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = oplinkF-tcpfrontend
BUNDLE_NAME_QT5 = $${BUNDLE_NAME}-qt5
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}

SOURCES += \
    tcpfrontendplugin.cpp

HEADERS += \
    tcpfrontendplugin.h

# meta file name for this bundle
DISTFILES += ../$${BUNDLE_NAME}bundle.json

# include dir for compilation
INCLUDEPATH += \
        ../lib \
        ../../../core-lib \
        ../../../../../plugframe/core-lib

LIBS    +=  -l$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}.a
