QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

OL_CLIENT_LAUNCHER_VERSION = $$cat(./oplink-frontend-launcher.ver)
TARGET = oplink-guiclient-qt5-$${OL_CLIENT_LAUNCHER_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../plugframe/launchers/guilauncher/main.cpp

INCLUDEPATH += ../../../plugframe/core-lib

OTHER_FILES += \
               elekdom.qss \
               oplink-frontend-launcher.ver \
               properties.ini

RESOURCES += \
    oplink-frontend_resources.qrc

#PLugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../plugframe/core-lib/pfcore-lib.ver)
LIBS += -lplugframe-core-qt5-$${PF_LIB_VERSION} -L../../../plugframe/core-lib

#OpLink LIB
###########
OL_LIB_VERSION = $$cat(../core-lib/olcore-lib.ver)
LIBS += -loplink-core-qt5-$${OL_LIB_VERSION} -L../core-lib

# Default rules for deployment.
DESTDIR = ../../../bin/oplink_guifrontend
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
