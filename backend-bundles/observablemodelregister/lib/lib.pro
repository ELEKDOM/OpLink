QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-observablemodelregister-qt6-$${BUNDLE_VERSION}

SOURCES +=  \
            modelregisterservice.cpp \
            observablebuilderservice.cpp \
            observablemodelregister.cpp \
            observablemodelregisterfactory.cpp \
            observablemodelregisterserviceimplementation.cpp

HEADERS +=  \
            modelregisterservice.h \
            observablebuilderservice.h \
            observablemodelregister.h \
            observablemodelregister_forward.h \
            observablemodelregisterfactory.h \
            observablemodelregisterserviceimplementation.h

INCLUDEPATH += \
               ../plugin \
               ../../../core-lib \
               ../../../core-backend-lib \
               ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
