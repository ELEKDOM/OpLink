QT       -= gui
QT += network xml

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkF-tcpfrontend-qt6-$${BUNDLE_VERSION}

SOURCES += \
         tcpfrontend.cpp \
         tcpfrontenddeserializer.cpp \
         tcpfrontendfactory.cpp

HEADERS += \
         tcpfrontend.h \
         tcpfrontenddeserializer.h \
         tcpfrontendfactory.h \
         tcpfrontendlogchannel.h

# include dir for compilation
INCLUDEPATH +=  \
        ../plugin \
        ../../../core-lib \
        ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
