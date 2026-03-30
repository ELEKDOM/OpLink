#include "heatingmanagermodel.h"
#include "heatingmanagerbuilderargs.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanager.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/pilotwirethermostatcontrolroom.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/statetowatch.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/processor/heatingmanagersetprocessor.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/processor/heatingmanagerroomprocessor.h"
#include "observable/property/propertyid.h"
#include "observable/values.h"
#include "logger/pflog.h"

oplink::HeatingManagerModel::HeatingManagerModel(const ObservableModelName& name):
    SupervisorObservableModel{name}
{

}

oplink::HeatingManagerModel::~HeatingManagerModel()
{

}

bool oplink::HeatingManagerModel::checkBuilderArgs(QspObservableBuilderArgs builderArgs)
{
    bool ret{false};
    QspHeatingManagerBuilderArgs hManagerArgs{builderArgs.dynamicCast<HeatingManagerBuilderArgs>()};

    ret = !hManagerArgs.isNull() && hManagerArgs->m_observableService;

    return ret;
}

oplink::ObservableBuilder *oplink::HeatingManagerModel::createInstance(QspObservableBuilderArgs builderArgs)
{
    HeatingManager *ret{nullptr};
    QspHeatingManagerBuilderArgs hManagerArgs{builderArgs.dynamicCast<HeatingManagerBuilderArgs>()};
    QString defaultSetpointValue; // default value to pass in to the manager

    // Caution, the default setpoint value depends of the type of control !
    if (HeatingManagerLoaderHook::ControlType::PW == hManagerArgs->m_controlType)
    {
        defaultSetpointValue = CommandArgs::OFF; // default pilot wire order
    }
    else if (HeatingManagerLoaderHook::ControlType::PWT == hManagerArgs->m_controlType)
    {
        defaultSetpointValue = "0"; // default temperature setpoint
    }

    ret = new HeatingManager{defaultSetpointValue, hManagerArgs->m_schedul};

    return ret;
}

///
/// \brief oplink::HeatingManagerModel::buildProperties
/// builds heating manager properties
/// \param observableBuilder
/// \param builderArgs
/// \return
///
bool oplink::HeatingManagerModel::buildProperties(QspObservableBuilder observableBuilder, QspObservableBuilderArgs builderArgs)
{
    bool ret;
    QspHeatingManagerBuilderArgs hManagerArgs{builderArgs.dynamicCast<HeatingManagerBuilderArgs>()};

    // mandatory properties: name, location and model name
    ObservableModel::buildProperties(observableBuilder,builderArgs);

    // Specific properties for a HeatingManager
    //-----------------------------------------
    try
    {
        // running State
        ret = addRunningProperty(observableBuilder, hManagerArgs->m_activated);
        if (!ret)
        {
            throw("RunningState");
        }

        // setpoint value
        ret = addSetpointProperty(observableBuilder, hManagerArgs->m_setPoint);
        if (!ret)
        {
            throw("Setpoint");
        }

        // a defined scheduler ?
        if (hManagerArgs->m_setPointScheduled)
        {
            // mode : ondemand or planned !
            ret = addTriggerMode(observableBuilder, hManagerArgs->m_setPoint);
            if (!ret)
            {
                throw("TriggerMode");
            }

            // scheduler definition for frontend !
            ret = addSchedulerXmlDefinitionProperty(observableBuilder, hManagerArgs->m_schedulXmlText);
            if (!ret)
            {
                throw("SchedulerXmlDefinition");
            }

            // derogated flag
            ret = addDerogatedProperty(observableBuilder);
            if (!ret)
            {
                throw("Derogated");
            }
        }
    }
    catch (QString& propErr)
    {
        pfWarning1(logChannel()) << QObject::tr("Erreur lors de la construction de %1, propriété %2 non créée!").arg(builderArgs->m_observableName, propErr);
    }

    // Specific properties per rooms
    //------------------------------
    ret = addRoomProperties(observableBuilder, builderArgs);

    return ret;
}

bool oplink::HeatingManagerModel::buildProcessors(QspObservableBuilder observableBuilder, QspObservableBuilderArgs builderArgs)
{
    bool ret{true};
    CommandProcessor *newProcessor;

    // Create and add 'set' processor
    newProcessor = createSetProcessor(observableBuilder->toObservable());
    if (newProcessor)
    {
        observableBuilder->addProcessor(newProcessor);
    }

    // Create and add 'room' processor
    newProcessor = createRoomProcessor(observableBuilder->toObservable());
    if (newProcessor)
    {
        observableBuilder->addProcessor(newProcessor);
    }

    return ret;
}

void oplink::HeatingManagerModel::postBuild(QspObservableBuilder observableBuilder, QspObservableBuilderArgs builderArgs)
{
    QspHeatingManagerBuilderArgs hManagerArgs{builderArgs.dynamicCast<HeatingManagerBuilderArgs>()};
    HeatingManager& heatingManager{dynamic_cast<oplink::HeatingManager&>(observableBuilder->toObservable())};
    bool ok{true};

    // Now all properties are built, add a "monitored group" per room
    //---------------------------------------------------------------

    for (auto i = 0; i < hManagerArgs->m_rooms.size(); i++)
    {
        QspGroupToWatch monitoredRoom;
        QspGroupToWatchAlgorithm controlRoom{createControlRoom(observableBuilder,builderArgs,i)};
        ok = !controlRoom.isNull();
        if (ok)
        {
            monitoredRoom.reset(new GroupToWatch{controlRoom});
            ok = !monitoredRoom.isNull();
            if (ok)
            {
                QString observableName;
                QString propertyName;
                QspStateToWatch monitoredState;

                monitoredRoom->groupName(hManagerArgs->m_rooms[i]->m_name);
                monitoredRoom->setObservableService(hManagerArgs->m_observableService);// to subcribe/unsubscribe to monitored observables !

                // monitored heaters
                monitoredRoom->addCategory(HeatingManager::heaterCategory());
                for (auto j = 0; j < hManagerArgs->m_rooms[i]->m_heaters.size(); j++)
                {
                    observableName = hManagerArgs->m_rooms[i]->m_heaters[j]->m_observableName;
                    propertyName = hManagerArgs->m_rooms[i]->m_heaters[j]->m_propertyName;
                    if (!observableName.isEmpty() && !propertyName.isEmpty())
                    {

                        monitoredState.reset(createStateToWatch(observableName,
                                                                propertyName,
                                                                builderArgs));

                        if (!monitoredState.isNull())
                        {
                            monitoredRoom->addMonitoredState(HeatingManager::heaterCategory(),
                                                             monitoredState);
                        }
                    }
                }

                // monitored window sensors
                if (hManagerArgs->m_rooms[i]->m_wod)
                {
                    monitoredRoom->addCategory(HeatingManager::windowSensorCategory());
                    for (auto j = 0; j < hManagerArgs->m_rooms[i]->m_windowSensors.size(); j++)
                    {
                        observableName = hManagerArgs->m_rooms[i]->m_windowSensors[j]->m_observableName;
                        propertyName = hManagerArgs->m_rooms[i]->m_windowSensors[j]->m_propertyName;
                        if (!observableName.isEmpty() && !propertyName.isEmpty())
                        {

                            monitoredState.reset(createStateToWatch(observableName,
                                                                    propertyName,
                                                                    builderArgs));

                            if (!monitoredState.isNull())
                            {
                                monitoredRoom->addMonitoredState(HeatingManager::windowSensorCategory(),
                                                                monitoredState);
                            }
                        }
                    }
                }

                // monitored temp sensors
                if (HeatingManagerLoaderHook::ControlType::PWT == hManagerArgs->m_controlType)
                {
                    monitoredRoom->addCategory(HeatingManager::temperatureSensorCategory());
                    for (auto j = 0; j < hManagerArgs->m_rooms[i]->m_tempSensors.size(); j++)
                    {
                        observableName = hManagerArgs->m_rooms[i]->m_tempSensors[j]->m_observableName;
                        propertyName = hManagerArgs->m_rooms[i]->m_tempSensors[j]->m_propertyName;
                        if (!observableName.isEmpty() && !propertyName.isEmpty())
                        {

                            monitoredState.reset(createStateToWatch(observableName,
                                                                    propertyName,
                                                                    builderArgs));

                            if (!monitoredState.isNull())
                            {
                                monitoredRoom->addMonitoredState(HeatingManager::temperatureSensorCategory(),
                                                                 monitoredState);
                            }
                        }
                    }
                }

                // one more group to monitor !
                heatingManager.addMonitoredObservableGroup(monitoredRoom->groupName(),monitoredRoom);
            }
        }
    }

    if(!ok)
    {
        pfWarning1(logChannel()) << QObject::tr("Erreur lors de la construction des groupes à surveiller de %1 !").arg(builderArgs->m_observableName);
    }
}

bool oplink::HeatingManagerModel::addSetpointProperty(const QspObservableBuilder &observableBuilder, const QString &value)
{
    bool ret;
    QString setpointVal;

    // for a scheduledSetPoint, its value is given at scheduler starting !
    if (HeatingManagerLoaderHook::scheduledSetPoint() != value)
    {
        setpointVal = value;
    }

    ret = addProperty(observableBuilder,
                      PropertyId::P_SETPOINT,
                      setpointVal,
                      true);
    return ret;
}

bool oplink::HeatingManagerModel::addTriggerMode(const QspObservableBuilder &observableBuilder, const QString &value)
{
    bool ret;
    QString mode;

    // fselect the triggered mode
    if (HeatingManagerLoaderHook::scheduledSetPoint() != value)
    {
        mode = Values::TRIGGER_MODE_PLANNED;
    }
    else
    {
        mode = Values::TRIGGER_MODE_ONDEMAND;
    }

    ret = addTriggerModeProperty(observableBuilder, mode);

    return ret;
}

bool oplink::HeatingManagerModel::addDerogatedProperty(const QspObservableBuilder &observableBuilder)
{
    bool ret, value{false};

    ret = addProperty(observableBuilder,
                      PropertyId::P_DEROGATED,
                      value,
                      true);
    return ret;
}

bool oplink::HeatingManagerModel::addRoomProperties(const QspObservableBuilder &observableBuilder,
                                                    const QspObservableBuilderArgs &builderArgs)
{
    bool ret;
    QspHeatingManagerBuilderArgs hManagerArgs{builderArgs.dynamicCast<HeatingManagerBuilderArgs>()};
    QString gpName;

    try
    {
        for (auto i = 0; i < hManagerArgs->m_rooms.size(); i++)
        {
            gpName = PropertyId::groupPropertyName(hManagerArgs->m_rooms[i]->m_name, PropertyId::P_SETPOINT);
            ret = addProperty(observableBuilder,gpName);
            if (!ret)
            {
                throw(gpName);
            }

            gpName = PropertyId::groupPropertyName(hManagerArgs->m_rooms[i]->m_name, PropertyId::P_WCLOSED);
            ret = addProperty(observableBuilder,gpName);
            if (!ret)
            {
                throw(gpName);
            }

            gpName = PropertyId::groupPropertyName(hManagerArgs->m_rooms[i]->m_name, PropertyId::P_TEMPERATURE);
            ret = addProperty(observableBuilder,gpName);
            if (!ret)
            {
                throw(gpName);
            }
        }
    }
    catch (QString& propErr)
    {
        pfWarning1(logChannel()) << QObject::tr("Erreur lors de la construction de %1, propriété de groupe %2 non créée!").arg(builderArgs->m_observableName, propErr);
    }

    return ret;
}

oplink::PilotWireControlRoom *oplink::HeatingManagerModel::createControlRoom(const QspObservableBuilder &observableBuilder, const QspObservableBuilderArgs &builderArgs, int roomIdx)
{
    QspHeatingManagerBuilderArgs hManagerArgs{builderArgs.dynamicCast<HeatingManagerBuilderArgs>()};
    HeatingManager& heatingManager{dynamic_cast<oplink::HeatingManager&>(observableBuilder->toObservable())};
    PilotWireControlRoom *ret{nullptr};

    if (HeatingManagerLoaderHook::ControlType::PW == hManagerArgs->m_controlType)
    {
        ret = new PilotWireControlRoom{heatingManager,
                                       hManagerArgs->m_rooms[roomIdx]->m_wod};
    }
    else if (HeatingManagerLoaderHook::ControlType::PWT == hManagerArgs->m_controlType)
    {
        ret = new PilotWireThermostatControlRoom{heatingManager,
                                                 hManagerArgs->m_rooms[roomIdx]->m_wod,
                                                 hManagerArgs->m_max_temp,
                                                 hManagerArgs->m_threshold};
    }

    return ret;
}

oplink::CommandProcessor *oplink::HeatingManagerModel::createRoomProcessor(Observable &parent)
{
    return new HeatingManagerRoomProcessor{parent};
}

oplink::CommandProcessor *oplink::HeatingManagerModel::createSetProcessor(Observable &parent)
{
    return new HeatingManagerSetProcessor{parent};
}
