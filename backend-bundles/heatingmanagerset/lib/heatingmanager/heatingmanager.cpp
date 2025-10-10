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
#include "observable/highobservable/monitor/grouptowatch.h"
#include "observable/highobservable/monitor/grouptowatchalgorithm.h"
#include "logger/pflog.h"

using namespace elekdom::oplink::core;
using namespace elekdom::oplink::heatingmanager;

HeatingManager::HeatingManager() {}

HeatingManager::~HeatingManager()
{

}

bool HeatingManager::windowSensorState(const QString &roomName, bool allClosed)
{
    bool ret{isActivated()};

    if (ret)
    {
        // Notify property update
        QString pName {observable::PropertyId::groupPropertyName(roomName,
                                                                 observable::PropertyId::P_WCLOSED)};
        observable::QspProperty prop{property(pName)};

        if (!prop.isNull())
        {
            prop->changeValue(allClosed);
        }
    }

    return ret;
}

void HeatingManager::heaterState(const QString &roomName, QString pwm)
{
    pfDebug3(logChannel()) << "->HeatingManager::heaterState, roomName = " << roomName << " pwm = " << pwm;

    if (isActivated())
    {
        QString mOrder{managerOrder()};
        QString rOrder{roomOrder(roomName)};

        //Check for heater derogation ?
        if (mOrder != pwm)
        {
            managerDerogated();
        }

        // Check for room derogation ?
        if (rOrder != pwm)
        {
            roomDerogated(roomName, true);
        }
    }

    pfDebug3(logChannel()) << "<-HeatingManager::heaterState";
}

void HeatingManager::specificInit(engine::service::ObservableServiceInterface *observableService)
{
    // initialization depends on the mode value
    QString modeValStr{mode()};

    if (offMode() != modeValStr && (manualMode() == modeValStr ||
                                 scheduledMode() == modeValStr ||
                                 manualDerogatedMode() == modeValStr ||
                                 scheduledDerogatedMode() == modeValStr))
    {
        initGroupAlgotithms(observableService);
    }
}

void HeatingManager::onSchedulerEvt(QString evt)
{
    pfDebug3(logChannel()) << "->HeatingManager::onSchedulerEvt, evt = " << evt;

    // The manager must be in Scheduled mode to process the event
    QString modeValStr{mode()};

    if (scheduledMode() == modeValStr || scheduledDerogatedMode() == modeValStr)
    {
        mode(scheduledMode());
        processScheduledOrder(evt);
    }

    pfDebug3(logChannel()) << "<-HeatingManager::onSchedulerEvt";
}

const QString HeatingManager::managerOrder()
{
    QString ret;

    observable::QspProperty prop{property(observable::PropertyId::P_ORDER)};

    if (!prop.isNull())
    {
        ret = prop->value().toString();
    }

    return ret;
}

void HeatingManager::managerOrder(const QString &order)
{
    pfDebug3(logChannel()) << "->HeatingManager::managerOrder, order = " << order;

    observable::QspProperty prop{property(observable::PropertyId::P_ORDER)};

    prop->changeValue(order);

    pfDebug3(logChannel()) << "<-HeatingManager::managerOrder";
}

void HeatingManager::managerDerogated()
{
    pfDebug3(logChannel()) << "->HeatingManager::managerDerogated";

    QString mm{mode()};
    QString derog;

    if (mm == scheduledMode())
    {
        derog = scheduledDerogatedMode();
    }
    else if (mm == manualMode())
    {
        derog = manualDerogatedMode();
    }

    if (!derog.isEmpty())
    {
        mode(derog);
    }

    pfDebug3(logChannel()) << "<-HeatingManager::managerDerogated";
}

const QString HeatingManager::roomOrder(const QString &roomName)
{
    QString ret;
    QString propId{observable::PropertyId::groupPropertyName(roomName,
                                                             observable::PropertyId::P_DEROGATED_ORDER)};
    observable::QspProperty prop{property(propId)};

    if (!prop.isNull())
    {
        ret = prop->value().toString();
    }

    return ret;
}

void HeatingManager::roomOrder(const QString &roomName, const QString &order)
{
    QString propId{observable::PropertyId::groupPropertyName(roomName,
                                                             observable::PropertyId::P_DEROGATED_ORDER)};
    observable::QspProperty prop{property(propId)};
    QVariant val(order);

    prop->changeValue(val);
}

bool HeatingManager::roomDerogated(const QString &roomName)
{
    QString propId{observable::PropertyId::groupPropertyName(roomName,
                                                             observable::PropertyId::P_DEROGATED)};
    observable::QspProperty prop{property(propId)};
    QVariant val;

    val = prop->value();

    return val.toBool();
}

void HeatingManager::roomDerogated(const QString &roomName, bool flag)
{
    pfDebug3(logChannel()) << "->HeatingManager::roomDerogated, roomName = " << roomName << " flag = " << flag;

    QString propId{observable::PropertyId::groupPropertyName(roomName,
                                                             observable::PropertyId::P_DEROGATED)};
    observable::QspProperty prop{property(propId)};
    QVariant val(flag);

    prop->changeValue(val);

    pfDebug3(logChannel()) << "->HeatingManager";
}

void HeatingManager::processScheduledOrder(const QString &order)
{
    const HashGroup& rooms{groups()};

    //update manager's property
    managerOrder(order);

    // For each rooms
    for (HashGroup::const_iterator i = rooms.constBegin(); i != rooms.constEnd(); i++)
    {
        QString roomName{i.key() };
        PilotWireControlRoom *ptrControlRoomAlgo{dynamic_cast<PilotWireControlRoom*>((i.value())->algorithm())};

        roomDerogated(roomName, false);
        roomOrder(roomName, order);
        if (ptrControlRoomAlgo)
        {
            ptrControlRoomAlgo->orderForHeaters(order);
        }
    }
}
