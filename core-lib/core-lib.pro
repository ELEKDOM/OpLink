QT -= gui
QT += xml
CONFIG += c++11

TEMPLATE = lib
DEFINES += OLCORE_LIBRARY

OL_LIB_VERSION = $$cat(olcore-lib.ver)
TARGET = oplink-core-qt5-$${OL_LIB_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    command/command-names.cpp \
    frontendtypes.cpp \
    network_tcp/downloadconfigmessage.cpp \
    network_tcp/downloadconfigreplymessage.cpp \
    network_tcp/message.cpp \
    network_tcp/readymessage.cpp \
    network_tcp/sessionmessage.cpp \
    network_tcp/sessionstartedmessage.cpp \
    network_tcp/signinmessage.cpp \
    network_tcp/signinreplymessage.cpp \
    network_tcp/signoutmessage.cpp \
    network_tcp/statevaluemessage.cpp \
    network_tcp/submitordermessage.cpp \
    observable/heatingmanager/heatingmanagerconfdocument.cpp \
    observable/remote/sessionconfdocument.cpp \
    observable/type.cpp \
    observable/values.cpp \
    observable/virtualequipment/virtualequipmentconfdocument.cpp

HEADERS += \
    frontendtypes.h \
    network_tcp/downloadconfigmessage.h \
    network_tcp/downloadconfigreplymessage.h \
    network_tcp/message.h \
    network_tcp/messagetype.h \
    network_tcp/readymessage.h \
    network_tcp/sessionmessage.h \
    network_tcp/sessionstartedmessage.h \
    network_tcp/signinmessage.h \
    network_tcp/signinreplymessage.h \
    network_tcp/signoutmessage.h \
    network_tcp/statevaluemessage.h \
    network_tcp/submitordermessage.h \
    observable/heatingmanager/heatingmanagerconfdocument.h \
    observable/heatingmanager/heatingmanagerloaderhook.h \
    observable/remote/sessionconfdocument.h \
    observable/remote/sessionconfhook.h \
    observable/values.h \
    observable/virtualequipment/virtualequipmentconfdocument.h \
    observable/virtualequipment/virtualequipmentloaderhook.h \
    olcore-lib_export.h \
    command/command-names.h \
    observable/type.h \
    olcore-lib_forward.h

OTHER_FILES += olcore-lib.ver

INCLUDEPATH += \
            ../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

