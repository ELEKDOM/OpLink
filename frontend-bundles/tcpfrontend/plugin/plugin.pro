QT -= gui
QT += network

TEMPLATE = lib
CONFIG  += plugin

BUNDLE_NAME = oplinkF-tcpfrontend
BUNDLE_NAME_QT = $${BUNDLE_NAME}-qt6
BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = $${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}

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

LIBS    +=  -l$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION} -L../lib
PRE_TARGETDEPS += ../lib/lib$${BUNDLE_NAME_QT}-$${BUNDLE_VERSION}.a

#OpLink LIB
###########
OL_LIB_VERSION = $$cat(../../../core-lib/olcore-lib.ver)
LIBS += -loplink-core-qt6-$${OL_LIB_VERSION} -L../../../core-lib

#PlugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../../../plugframe/core-lib/pfcore-lib.ver)
PF_LIB_NAME = plugframe-core-qt6-$${PF_LIB_VERSION}
LIBS += -l$${PF_LIB_NAME} -L../../../../../plugframe/core-lib
