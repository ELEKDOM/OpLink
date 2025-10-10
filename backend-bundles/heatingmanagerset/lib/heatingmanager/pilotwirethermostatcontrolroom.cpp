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


#include "pilotwirethermostatcontrolroom.h"
#include "heatingmanager.h"
#include "observable/highobservable/monitor/grouptowatch.h"
#include "observable/values.h"
#include "logger/pflog.h"

using namespace elekdom::oplink::heatingmanager;
using namespace elekdom::oplink::core;

PilotWireThermostatControlRoom::PilotWireThermostatControlRoom(core::observable::SupervisorObservable &manager,bool wod,bool pd,double max_temp,double threshold):
    PilotWireControlRoom{manager,wod,pd},
    m_max_temp{max_temp},
    m_threshold{threshold},
    m_temp_order{0},
    m_last_temp{0},
    m_last_regulation_order{observable::Values::PW_MODE_STOP}
{

}

PilotWireThermostatControlRoom::~PilotWireThermostatControlRoom()
{

}

void PilotWireThermostatControlRoom::initAlgo()
{
    observable::monitoring::GroupToWatch *myRoom{group()};

    PilotWireControlRoom::initAlgo();

    // temp sensors
    subscribeToCategory(HeatingManager::temperatureSensorCategory(),
                        myRoom,
                        observableService());
}

void PilotWireThermostatControlRoom::orderForHeaters(const QString &order)
{
    pfInfo2(manager().logChannel()) << tr("HeaterManager %1 nouvelle consigne %2° pour la pièce %3").arg(manager().name(), order, group()->groupName());

    m_temp_order = order.toDouble();
    if (m_temp_order > m_max_temp)
    {
        m_temp_order = m_max_temp;
    }
    regulHeaters();
}

void PilotWireThermostatControlRoom::onStateChangeFromHeaters(const core::observable::ObservableName& observableName,
                                                              const core::observable::PropertyName& propertyName,
                                                              QVariant propertyValue)
{
    quint8 val;

    pfInfo2(manager().logChannel()) << tr("HeaterManager %1 pièce %2 nouvel état %3 %4").arg(manager().name(), group()->groupName(), observableName, propertyValue.toString());

    val = propertyValue.toUInt();

    if (wod() && !roomClosed())
    {
        if (val != observable::Values::PW_MODE_STOP)
        {
            // Force stop, windows are open !
            pwmHeater(observableName,propertyName,command::CommandArgs::OFF);
            pfInfo2(manager().logChannel()) << tr("> %1 commandé à OFF").arg(observableName);
        }
    }
    else if (val != m_last_regulation_order)
    {
        // Force to last order
        pwmHeater(observableName,propertyName,convertPWM2str(m_last_regulation_order));
        pfInfo2(manager().logChannel()) << tr("> %1 commandé à %2").arg(observableName).arg(m_last_regulation_order);
    }
}

void PilotWireThermostatControlRoom::onStateChangeFromTemperatureSensors(const core::observable::ObservableName& observableName,
                                                                         const core::observable::PropertyName& propertyName,
                                                                         QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    m_last_temp = propertyValue.toDouble();

    pfInfo2(manager().logChannel()) << tr("HeaterManager %1 pièce %2 acquisition température %3°").arg(manager().name(), group()->groupName(), propertyValue.toString());

    regulHeaters();
}

void PilotWireThermostatControlRoom::regulHeaters()
{
    if (m_last_temp > m_temp_order)
    {
        m_last_regulation_order = observable::Values::PW_MODE_STOP;
        turnOffHeaters();
        pfInfo2(manager().logChannel()) << tr("HeaterManager %1 pièce %2 régulation > radiateurs à OFF").arg(manager().name(), group()->groupName());
    }
    else if (m_last_temp < (m_temp_order - m_threshold))
    {
        m_last_regulation_order = observable::Values::PW_MODE_COMFORT;
        turnComfortHeaters();
        pfInfo2(manager().logChannel()) << tr("HeaterManager %1 pièce %2 régulation > radiateurs à COMFORT").arg(manager().name(), group()->groupName());
    }
}
