QT       -= gui

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = oplinkB-console
BUNDLE_NAME_QT = $${BUNDLE_NAME}-qt6
BUNDLE_VERSION = $$cat(../bundle.ver)

# this bundle replaces the smf console
TARGET = $${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}

SOURCES += \
    olconsoleplugin.cpp

HEADERS += \
    olconsoleplugin.h

# meta file name for this bundle
DISTFILES += ../$${BUNDLE_NAME}bundle.json

# include dir for compilation
INCLUDEPATH +=  \
        ../lib \
        ../../../core-lib \
        ../../../core-backend-lib \
        ../../../../../plugframe/core-lib \
        ../../../../../plugframe/bundles/console/lib

RESOURCES +=

LIBS    +=  -l$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}.a

# oplink's console extends plugframe's one
##########################################
PF_BUNDLE_VERSION = $$cat(../../../../../plugframe/bundles/console/bundle.ver)
PF_BUNDLE_NAME_QT = console-qt6
LIBS    +=  -l$${PF_BUNDLE_NAME_QT}-$${PF_BUNDLE_VERSION} -L../../../../../plugframe/bundles/console/lib
PRE_TARGETDEPS += ../../../../../plugframe/bundles/console/lib/lib$${PF_BUNDLE_NAME_QT}-$${PF_BUNDLE_VERSION}.a

#OpLink BACKEND LIB
###################
OL_BACKEND_LIB_VERSION = $$cat(../../../core-backend-lib/olcore-backend-lib.ver)
LIBS += -loplink-core-backend-qt6-$${OL_BACKEND_LIB_VERSION} -L../../../core-backend-lib

#PlugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../../../plugframe/core-lib/pfcore-lib.ver)
PF_LIB_NAME = plugframe-core-qt6-$${PF_LIB_VERSION}
LIBS += -l$${PF_LIB_NAME} -L../../../../../plugframe/core-lib
