QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

OL_LAUNCHER_VERSION = $$cat(./oplink-backend-launcher.ver)
TARGET = oplink-server-qt6-$${OL_LAUNCHER_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../../plugframe/launchers/consolelauncher/main.cpp

INCLUDEPATH += ../../../plugframe/core-lib

OTHER_FILES += \
               oplink-backend-launcher.ver \
               properties.ini

#PLugFrame LIB
##############
PF_LIB_VERSION = $$cat(../../../plugframe/core-lib/pfcore-lib.ver)
LIBS += -lplugframe-core-qt6-$${PF_LIB_VERSION} -L../../../plugframe/core-lib

#OpLink LIB
###########
OL_LIB_VERSION = $$cat(../core-lib/olcore-lib.ver)
LIBS += -loplink-core-qt6-$${OL_LIB_VERSION} -L../core-lib

#OpLink BACKEND LIB
###################
OL_BACKEND_LIB_VERSION = $$cat(../core-backend-lib/olcore-backend-lib.ver)
LIBS += -loplink-core-backend-qt6-$${OL_BACKEND_LIB_VERSION} -L../core-backend-lib

# Default rules for deployment.
DESTDIR = ../../../bin/oplink_backend
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
