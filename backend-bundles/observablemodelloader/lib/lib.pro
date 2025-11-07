QT       -= gui
QT       += xml

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkB-observablemodelloader-qt6-$${BUNDLE_VERSION}

SOURCES += \
        event/mandatorypropertiesmodelloadingevent.cpp \
        event/observablemodelsloadingevent.cpp \
        event/specificpropertiesmodelloadingevent.cpp \
        event/processorsmodelloadingevent.cpp \
        observablemodelloaderfactory.cpp \
        observablemodelloaderlistener.cpp \
        observablemodelloader.cpp \
        observablemodelloaderemitter.cpp

HEADERS += \
        event/mandatorypropertiesmodelloadingevent.h \
        event/observablemodelsloadingevent.h \
        event/specificpropertiesmodelloadingevent.h \
        event/processorsmodelloadingevent.h \
        observablemodelloaderfactory.h \
        observablemodelloaderlistener.h \
        observablemodelloader.h \
        observablemodelloader_forward.h \
        observablemodelloaderemitter.h

INCLUDEPATH += \
        ../../../core-lib \
        ../../../core-backend-lib \
        ../../../../../plugframe/core-lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
