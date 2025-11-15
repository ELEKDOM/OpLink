
QT += core xml
QT -= gui

TEMPLATE = lib
DEFINES += OLCORE_BACKEND_LIBRARY

CONFIG += c++17

OL_BACKEND_LIB_VERSION = $$cat(olcore-backend-lib.ver)
TARGET = oplink-core-backend-qt6-$${OL_BACKEND_LIB_VERSION}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        abstract_infrastructure/area/area.cpp \
        abstract_infrastructure/area/areagateway.cpp \
        abstract_infrastructure/area/gatewayargs.cpp \
        abstract_infrastructure/device/device.cpp \
        abstract_infrastructure/device/devicecommandprocessor.cpp \
        abstract_infrastructure/infrastructure.cpp \
        abstract_infrastructure/infrastructurefactory.cpp \
        abstract_infrastructure/loading/actuatoroutput.cpp \
        abstract_infrastructure/loading/actuatoroutputsbinding.cpp \
        abstract_infrastructure/loading/devicebuilder.cpp \
        abstract_infrastructure/loading/devicechannelsbinding.cpp \
        abstract_infrastructure/loading/deviceprocessorbuilder.cpp \
        abstract_infrastructure/loading/infrastructureconfreader.cpp \
        abstract_infrastructure/loading/infrastructureloader.cpp \
        abstract_infrastructure/loading/infrastructureloaderargs.cpp \
        abstract_infrastructure/loading/infrastructureloaderouts.cpp \
        abstract_infrastructure/loading/infrastructurestore.cpp \
        abstract_infrastructure/loading/infrastructureworkerouts.cpp \
        abstract_infrastructure/plugin/infrastructureplugin.cpp \
        abstract_infrastructure/service/infrastructurecontrolservice.cpp \
        abstract_virtualequipementset/loading/virtualequipmentloader.cpp \
        abstract_virtualequipementset/loading/virtualequipmentsetconfreader.cpp \
        abstract_virtualequipementset/loading/virtualequipmentsetloader.cpp \
        abstract_virtualequipementset/loading/virtualequipmentsetloaderargs.cpp \
        abstract_virtualequipementset/loading/virtualequipmentsetloaderouts.cpp \
        abstract_virtualequipementset/plugin/virtualequipmentsetplugin.cpp \
        abstract_virtualequipementset/service/virtualequipmentsetservice.cpp \
        abstract_virtualequipementset/virtualequipmentset.cpp \
        abstract_virtualequipementset/virtualequipmentsetbuilder.cpp \
        abstract_virtualequipementset/virtualequipmentsetfactory.cpp \
        command/command.cpp \
        model/observable/actuatorbuilderargs.cpp \
        model/observable/actuatormodel.cpp \
        model/observable/loadbuilderargs.cpp \
        model/observable/loadmodel.cpp \
        model/observable/observablebuilderargs.cpp \
        model/observable/observablemodel.cpp \
        model/observable/operationdevicebuilderargs.cpp \
        model/observable/operationdevicemodel.cpp \
        model/observable/sensorbuilderargs.cpp \
        model/observable/sensormodel.cpp \
        model/processor/commandprocessormodel.cpp \
        model/processor/expectedvaluecheckcommandprocessormodel.cpp \
        model/processor/expectedvaluenocheckcommandprocessormodel.cpp \
        model/processor/loadcommandprocessormodel.cpp \
        model/processor/lowcommandprocessormodel.cpp \
        model/processor/operationdevicecommandprocessormodel.cpp \
        model/processormodelnames.cpp \
        model/property/actuatorpropertymodel.cpp \
        model/property/loadpropertymodel.cpp \
        model/property/observablepropertymodel.cpp \
        model/property/operationdevicepropertymodel.cpp \
        model/property/propertymodelnames.cpp \
        model/property/sensorpropertymodel.cpp \
        observable/highobservable/schedulableobservable.cpp \
        observable/highobservable/schedulerhook.cpp \
        observable/observable/observable.cpp \
        observable/observable/observablebuilder.cpp \
        observable/observable/observablebuilderscontainer.cpp \
        observable/observable/observableclassnames.cpp \
        observable/observable/observablenotifier.cpp \
        observable/observable/observablesubscriber.cpp \
        observable/lowobservable/lowobservable.cpp \
        observable/lowobservable/load.cpp \
        observable/lowobservable/operationdevice.cpp \
        observable/highobservable/highobservable.cpp \
        observable/highobservable/supervisorobservable.cpp \
        observable/highobservable/monitor/grouptowatch.cpp \
        observable/highobservable/monitor/grouptowatchalgorithm.cpp \
        observable/highobservable/monitor/statetowatch.cpp \
        observable/highobservable/monitor/statetowatchlist.cpp \
        observable/remote/observablestates.cpp \
        observable/remote/observablestatesgroup.cpp \
        observable/remote/sessionconfloader.cpp \
        observable/remote/subscribesession.cpp \
        observable/processor/commandprocessor.cpp \
        observable/processor/expectedvaluecheckprocessor.cpp \
        observable/processor/expectedvaluenocheckprocessor.cpp \
        observable/processor/loadcommandprocessor.cpp \
        observable/processor/lowcommandprocessor.cpp \
        observable/processor/operationdevicecommandprocessor.cpp \
        observable/processor/processorclassnames.cpp \
        observable/property/loadproperty.cpp \
        observable/property/lowproperty.cpp \
        observable/property/operationdeviceproperty.cpp \
        observable/property/property.cpp \
        observable/property/propertyclassnames.cpp \
        observable/property/propertyid.cpp

HEADERS += \
        olcore-backend-lib_export.h \
        olcore-backend-lib_forward.h \
        abstract_infrastructure/area/area.h \
        abstract_infrastructure/area/areagateway.h \
        abstract_infrastructure/area/gatewayargs.h \
        abstract_infrastructure/device/device.h \
        abstract_infrastructure/device/devicecommandprocessor.h \
        abstract_infrastructure/device/devicehook.h \
        abstract_infrastructure/infrastructure-names.h \
        abstract_infrastructure/infrastructure.h \
        abstract_infrastructure/infrastructurefactory.h \
        abstract_infrastructure/loading/actuatoroutput.h \
        abstract_infrastructure/loading/actuatoroutputsbinding.h \
        abstract_infrastructure/loading/confreadererror.h \
        abstract_infrastructure/loading/devicebuilder.h \
        abstract_infrastructure/loading/devicechannelsbinding.h \
        abstract_infrastructure/loading/deviceprocessorbuilder.h \
        abstract_infrastructure/loading/infrastructureconfreader.h \
        abstract_infrastructure/loading/infrastructureloader.h \
        abstract_infrastructure/loading/infrastructureloaderargs.h \
        abstract_infrastructure/loading/infrastructureloaderouts.h \
        abstract_infrastructure/loading/infrastructureloadingoperations.h \
        abstract_infrastructure/loading/infrastructurestore.h \
        abstract_infrastructure/loading/infrastructureworkerouts.h \
        abstract_infrastructure/plugin/infrastructureplugin.h \
        abstract_infrastructure/service/infrastructurecontrolservice.h \
        abstract_virtualequipementset/loading/virtualequipmentloader.h \
        abstract_virtualequipementset/loading/virtualequipmentsetconfreader.h \
        abstract_virtualequipementset/loading/virtualequipmentsetloader.h \
        abstract_virtualequipementset/loading/virtualequipmentsetloaderargs.h \
        abstract_virtualequipementset/loading/virtualequipmentsetloaderouts.h \
        abstract_virtualequipementset/plugin/virtualequipmentsetplugin.h \
        abstract_virtualequipementset/service/virtualequipmentsetservice.h \
        abstract_virtualequipementset/virtualequipmentset.h \
        abstract_virtualequipementset/virtualequipmentsetbuilder.h \
        abstract_virtualequipementset/virtualequipmentsetfactory.h \
        command/command.h \
        model/modellogchannel.h \
        model/modelnames.h \
        model/observable/actuatorbuilderargs.h \
        model/observable/actuatormodel.h \
        model/observable/loadbuilderargs.h \
        model/observable/loadmodel.h \
        model/observable/observablebuilderargs.h \
        model/observable/observablemodel.h \
        model/observable/operationdevicebuilderargs.h \
        model/observable/operationdevicemodel.h \
        model/observable/sensorbuilderargs.h \
        model/observable/sensormodel.h \
        model/processor/commandprocessormodel.h \
        model/processor/expectedvaluecheckcommandprocessormodel.h \
        model/processor/expectedvaluenocheckcommandprocessormodel.h \
        model/processor/loadcommandprocessormodel.h \
        model/processor/lowcommandprocessormodel.h \
        model/processor/operationdevicecommandprocessormodel.h \
        model/processormodelnames.h \
        model/property/actuatorpropertymodel.h \
        model/property/loadpropertymodel.h \
        model/property/observablepropertymodel.h \
        model/property/operationdevicepropertymodel.h \
        model/property/propertymodelnames.h \
        model/property/sensorpropertymodel.h \
        observable/observablelogchannel.h \
        observable/observablenames.h \
        observable/observable/observable.h \
        observable/observable/observablebuilder.h \
        observable/observable/observablebuilderscontainer.h \
        observable/observable/observableclassnames.h \
        observable/observable/observablenotifier.h \
        observable/observable/observablesubscriber.h \
        observable/lowobservable/lowobservable.h \
        observable/lowobservable/load.h \
        observable/lowobservable/operationdevice.h \
        observable/highobservable/highobservable.h \
        observable/highobservable/supervisorobservable.h \
        observable/highobservable/schedulableobservable.h \
        observable/highobservable/schedulerhook.h \
        observable/highobservable/monitor/grouptowatch.h \
        observable/highobservable/monitor/grouptowatchalgorithm.h \
        observable/highobservable/monitor/statetowatch.h \
        observable/highobservable/monitor/statetowatchlist.h \
        observable/remote/observablestates.h \
        observable/remote/observablestatesgroup.h \
        observable/remote/sessionconfloader.h \
        observable/remote/subscribesession.h \
        observable/processor/commandprocessor.h \
        observable/processor/expectedvaluecheckprocessor.h \
        observable/processor/expectedvaluenocheckprocessor.h \
        observable/processor/loadcommandprocessor.h \
        observable/processor/lowcommandprocessor.h \
        observable/processor/operationdevicecommandprocessor.h \
        observable/processor/processorclassnames.h \
        observable/property/loadproperty.h \
        observable/property/lowproperty.h \
        observable/property/operationdeviceproperty.h \
        observable/property/property.h \
        observable/property/propertyclassnames.h \
        observable/property/propertyid.h \
        service-int/infrastructurecontrolserviceinterface.h \
        service-int/modelregisterserviceinterface.h \
        service-int/observablebuilderserviceinterface.h \
        service-int/observableserviceinterface.h \
        service-int/virtualequipmentsetserviceinterface.h

OTHER_FILES += olcore-backend-lib.ver

INCLUDEPATH += \
            ../../../plugframe/core-lib \
            ../core-lib


CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
