QT       += gui \
            widgets

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = oplinkF-guiconsole
BUNDLE_NAME_QT5 = $${BUNDLE_NAME}-qt5
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}

SOURCES += \
    olfconsoleplugin.cpp

HEADERS += \
    olfconsoleplugin.h

# meta file name for this bundle
DISTFILES += ../$${BUNDLE_NAME}bundle.json

# include dir for compilation
INCLUDEPATH += \
        ../lib \
        ../../../core-lib \
        ../../../../../plugframe/core-lib \
        ../../../../../plugframe/bundles/guiconsole/lib

LIBS    +=  -l$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT5}-$${BUNDLE_VERSION}.a

# oplink's guiconsole extends plugframe's one
PF_BUNDLE_VERSION = $$cat(../../../../../plugframe/bundles/guiconsole/bundle.ver)
PF_BUNDLE_NAME_QT5 = guiconsole-qt5
LIBS    +=  -l$${PF_BUNDLE_NAME_QT5}-$${PF_BUNDLE_VERSION} -L../../../../../plugframe/bundles/guiconsole/lib
PRE_TARGETDEPS += ../../../../../plugframe/bundles/guiconsole/lib/lib$${PF_BUNDLE_NAME_QT5}-$${PF_BUNDLE_VERSION}.a
