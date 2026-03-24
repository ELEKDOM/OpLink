// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
// 
// This file is part of OpLink.
// 
// OpLink is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// OpLink is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//

#include <QVariant>
#include "heatingmanager.h"
#include "pilotwirecontrolroom.h"
#include "observable/property/propertyid.h"
#include "observable/property/property.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/grouptowatch.h"
#include "logger/pflog.h"

oplink::HeatingManager::HeatingManager(QString defaultSetpoint,const plugframe::QspScheduler& scheduler):
    SupervisorObservable{scheduler},
    m_defaultSetpoint{defaultSetpoint}
{

}

oplink::HeatingManager::~HeatingManager()
{

}

bool oplink::HeatingManager::windowSensorState(const QString &roomName, bool allClosed)
{
    bool ret{isOn()};

    pfInfo1(logChannel()) << QObject::tr("%1 pièce %2 nouvel état 'fenêtres fermées' : ").arg(name(),roomName) << allClosed;

    if (ret)
    {
        // Notify property update for the group (roomname)
        QString pName {oplink::PropertyId::groupPropertyName(roomName,
                       oplink::PropertyId::P_WCLOSED)};
        oplink::QspProperty prop{property(pName)};

        if (!prop.isNull())
        {
            prop->changeValue(allClosed);
        }
    }

    return ret;
}

void oplink::HeatingManager::init()
{
    // start room controls ?
    if (isOn())
    {
        startRoomsMonitor();
    }
}

void oplink::HeatingManager::onSchedulerEvt(QString evt)
{
    pfInfo1(logChannel()) << QObject::tr("%1 nouvelle consigne planifiée : ").arg(name()) << evt;

    if (isOn() && isPlannedMode())
    {
        derogatedProperty(false);
        processScheduledSetpoint(evt);
    }
}

void oplink::HeatingManager::startRoomsMonitor()
{
    QString currentEvt;

    // start the scheduler if it exists
    startScheduler(currentEvt);

    // set the setpoint if "planned mode"
    if (isPlannedMode())
    {
        if (currentEvt.isEmpty()) // caution, currentEvt could be ""
        {
            currentEvt = m_defaultSetpoint;
        }
        setpointProperty(currentEvt);
    }

    // start all room monitors
    subscribeToMonitoredObservables();
    setpointForRooms(setpointProperty());
}

void oplink::HeatingManager::stopRoomsMonitor()
{
    // stop the scheduler if it exists
    stopScheduler();

    // stop all room monitors
    unsubscribeToMonitoredObservables();
}

const QString oplink::HeatingManager::setpointProperty()
{
    QString ret;

    oplink::QspProperty prop{property(oplink::PropertyId::P_SETPOINT)};

    if (!prop.isNull())
    {
        ret = prop->value().toString();
    }

    return ret;
}

void oplink::HeatingManager::setpointProperty(const QString &setpoint)
{
    pfDebug3(logChannel()) << "->HeatingManager::managerSetpoint, setpoint = " << setpoint;

    oplink::QspProperty prop{property(oplink::PropertyId::P_SETPOINT)};

    prop->changeValue(setpoint);

    pfDebug3(logChannel()) << "<-HeatingManager::managerSetpoint";
}

const bool oplink::HeatingManager::derogatedProperty()
{
    bool ret{false};

    oplink::QspProperty prop{property(oplink::PropertyId::P_DEROGATED)};

    if (!prop.isNull())
    {
        ret = prop->value().toBool();
    }

    return ret;
}

void oplink::HeatingManager::derogatedProperty(bool derog)
{
    oplink::QspProperty prop{property(oplink::PropertyId::P_DEROGATED)};

    prop->changeValue(derog);
}

const QString oplink::HeatingManager::roomSetpointProperty(const QString &roomName)
{
    QString ret;
    QString propId{oplink::PropertyId::groupPropertyName(roomName,
                                                         oplink::PropertyId::P_SETPOINT)};
    oplink::QspProperty prop{property(propId)};

    if (!prop.isNull())
    {
        ret = prop->value().toString();
    }

    return ret;
}

void oplink::HeatingManager::roomSetpointProperty(const QString &roomName, const QString &order)
{
    QString propId{oplink::PropertyId::groupPropertyName(roomName,
                                                         oplink::PropertyId::P_SETPOINT)};
    oplink::QspProperty prop{property(propId)};
    QVariant val(order);

    prop->changeValue(val);
}

void oplink::HeatingManager::processScheduledSetpoint(const QString &setpoint)
{
    const HashGroup& rooms{groups()};

    // update manager's property
    setpointProperty(setpoint);

    // command all heaters
    setpointForRooms(setpoint);
}

void oplink::HeatingManager::setpointForRooms(const QString &setpoint)
{
    const HashGroup& rooms{groups()};

    // For each rooms
    for (HashGroup::const_iterator i = rooms.constBegin(); i != rooms.constEnd(); i++)
    {
        QString roomName{i.key() };
        PilotWireControlRoom *ptrControlRoomAlgo{dynamic_cast<PilotWireControlRoom*>((i.value())->algorithm())};

        roomSetpointProperty(roomName, setpoint);  // holds room setpoint as property
        if (ptrControlRoomAlgo)
        {
            ptrControlRoomAlgo->orderForHeaters(setpoint); // controls the room's radiators
        }
    }
}
