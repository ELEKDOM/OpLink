#! [0]
QT -= gui
QT += xml

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-heatingmanagerset-qt5-$${BUNDLE_VERSION}

SOURCES +=  \
            heatingmanagerset.cpp \
            heatingmanagersetfactory.cpp \
            heatingmanager/heatingmanagerloader.cpp \
            heatingmanager/heatingmanager.cpp \
            heatingmanager/pilotwirecontrolroom.cpp \
            heatingmanager/pilotwirethermostatcontrolroom.cpp

HEADERS +=  \
            heatingmanagerset_forward.h \
            heatingmanagerset.h \
            heatingmanagersetfactory.h \
            heatingmanagersetlogchannel.h \
            heatingmanager/heatingmanagerloader.h \
            heatingmanager/heatingmanager.h \
            heatingmanager/pilotwirecontrolroom.h \
            heatingmanager/pilotwirethermostatcontrolroom.h \

INCLUDEPATH +=  \
            ../plugin \
            ../../../core-lib \
            ../../../core-backend-lib \
            ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

