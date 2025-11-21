QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-engine-qt6-$${BUNDLE_VERSION}

SOURCES +=  \
            observableservice.cpp \
            serverengine.cpp \
            serverenginefactory.cpp \
            serverenginelistener.cpp \
            states/loadingvirtualequipmentsetsstate.cpp \
            states/serverstartingstate.cpp \
            states/startingclientsstate.cpp \
            states/startinginfrastructuresstate.cpp

HEADERS +=  \
            observableservice.h \
            serverengine.h \
            serverengine_forward.h \
            serverenginefactory.h \
            serverenginelistener.h \
            states/loadingvirtualequipmentsetsstate.h \
            states/serverstartingstate.h \
            states/startingclientsstate.h \
            states/startinginfrastructuresstate.h

INCLUDEPATH += \
        ../plugin \
        ../../../core-lib \
        ../../../core-backend-lib \
        ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
