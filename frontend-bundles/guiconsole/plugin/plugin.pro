QT       += gui \
            widgets \
            xml

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = oplinkF-guiconsole
BUNDLE_NAME_QT = $${BUNDLE_NAME}-qt6
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}

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

LIBS    +=  -l$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}.a

# oplink's guiconsole extends plugframe's one
PF_BUNDLE_VERSION = $$cat(../../../../../plugframe/bundles/guiconsole/bundle.ver)
PF_BUNDLE_NAME_QT = guiconsole-qt6
LIBS    +=  -l$${PF_BUNDLE_NAME_QT}-$${PF_BUNDLE_VERSION} -L../../../../../plugframe/bundles/guiconsole/lib
PRE_TARGETDEPS += ../../../../../plugframe/bundles/guiconsole/lib/lib$${PF_BUNDLE_NAME_QT}-$${PF_BUNDLE_VERSION}.a

#OpLink LIB
###########
OL_LIB_VERSION = $$cat(../../../core-lib/olcore-lib.ver)
LIBS += -loplink-core-qt6-$${OL_LIB_VERSION} -L../../../core-lib

#PlugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../../../plugframe/core-lib/pfcore-lib.ver)
PF_LIB_NAME = plugframe-core-qt6-$${PF_LIB_VERSION}
LIBS += -l$${PF_LIB_NAME} -L../../../../../plugframe/core-lib
