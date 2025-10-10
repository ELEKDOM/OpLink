QT -= gui
QT += network xml

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-tcpbackend-qt5-$${BUNDLE_VERSION}

SOURCES += \
         tcpbackend.cpp \
         tcpbackendchannelmanager.cpp \
         tcpbackenddeserializer.cpp \
         tcpbackendfactory.cpp

HEADERS += \
         tcpbackend.h \
         tcpbackend_forward.h \
         tcpbackendchannelmanager.h \
         tcpbackenddeserializer.h \
         tcpbackendfactory.h \
         tcpbackendlogchannel.h

# include dir for compilation
INCLUDEPATH +=  \
        ../plugin \
        ../../../core-lib \
        ../../../core-backend-lib \
        ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
