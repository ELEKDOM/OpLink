QT       -= gui

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-console-qt6-$${BUNDLE_VERSION}

SOURCES +=  \
            olcmdprocessor.cpp \
            olconsole.cpp \
            olconsolefactory.cpp \
            submitcmdprocessor.cpp \
            subscribecmdprocessor.cpp \
            subscribecmdprocessorhook.cpp \
            unsubscribecmdprocessor.cpp

HEADERS +=  \
            olcmdprocessor.h \
            olconsole.h \
            olconsole_forward.h \
            olconsolefactory.h \
            submitcmdprocessor.h \
            subscribecmdprocessor.h \
            subscribecmdprocessorhook.h \
            unsubscribecmdprocessor.h

INCLUDEPATH += \
        ../plugin \
        ../../../core-lib \
        ../../../core-backend-lib \
        ../../../../../plugframe/core-lib \
        ../../../../../plugframe/bundles/console/lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
