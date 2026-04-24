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
#include "observable/observable/highobservable/supervisorobservable/monitor/grouptowatch.h"
#include "observable/values.h"
#include "logger/pflog.h"

oplink::PilotWireThermostatControlRoom::PilotWireThermostatControlRoom(oplink::SupervisorObservable &manager,bool wod,double max_temp,double threshold):
    PilotWireControlRoom{manager,wod},
    m_max_temp{max_temp},
    m_threshold{threshold},
    m_temp_order{0},
    m_last_temp{0}
{

}

oplink::PilotWireThermostatControlRoom::~PilotWireThermostatControlRoom()
{

}

void oplink::PilotWireThermostatControlRoom::subscribe()
{
    oplink::GroupToWatch *myRoom{group()};

    PilotWireControlRoom::subscribe();

    // temp sensors
    subscribeToCategory(HeatingManager::temperatureSensorCategory(),
                        myRoom);
}

void oplink::PilotWireThermostatControlRoom::unsubscribe()
{
    oplink::GroupToWatch *myRoom{group()};

    PilotWireControlRoom::unsubscribe();

    // temp sensors
    unsubscribeToCategory(HeatingManager::temperatureSensorCategory(),
                          myRoom);
}

void oplink::PilotWireThermostatControlRoom::orderForHeaters(const QString &order)
{
    pfInfo2(manager().logChannel()) << tr("%1 nouvelle consigne %2° pour la pièce %3").arg(manager().name(), order, group()->groupName());

    m_temp_order = order.toDouble();
    if (m_temp_order > m_max_temp)
    {
        m_temp_order = m_max_temp;
    }
    regulHeaters();
}

void oplink::PilotWireThermostatControlRoom::onStateChangeFromTemperatureSensors(const oplink::ObservableName& observableName,
                                                                         const oplink::PropertyName& propertyName,
                                                                         QVariant propertyValue)
{
    PilotWireControlRoom::onStateChangeFromTemperatureSensors(observableName,propertyName,propertyValue); // to update manager temp property !
    m_last_temp = propertyValue.toDouble();
    pfInfo2(manager().logChannel()) << tr("%1 pièce %2 acquisition de la température à %3°").arg(manager().name(), group()->groupName(), propertyValue.toString());
    regulHeaters();
}

void oplink::PilotWireThermostatControlRoom::regulHeaters()
{
    pfInfo3(manager().logChannel()) << tr("%1 pièce %2 calcul régulation en cours").arg(manager().name(), group()->groupName());
    pfDebug4(manager().logChannel()) << "m_last_temp = " << m_last_temp << " , m_temp_order = " << m_temp_order;

    if (m_last_temp > m_temp_order)
    {
        lastRegulationOrder(oplink::Values::PW_MODE_STOP);
        turnOffHeaters();
        pfInfo2(manager().logChannel()) << tr("%1 pièce %2 régulation > radiateurs à OFF").arg(manager().name(), group()->groupName());
    }
    else if (m_last_temp < (m_temp_order - m_threshold))
    {
        lastRegulationOrder(oplink::Values::PW_MODE_COMFORT);
        turnComfortHeaters();
        pfInfo2(manager().logChannel()) << tr("%1 pièce %2 régulation > radiateurs à COMFORT").arg(manager().name(), group()->groupName());
    }
    else
    {
        pfInfo2(manager().logChannel()) << tr("%1 pièce %2 régulation, rien !").arg(manager().name(), group()->groupName());
    }
}

void oplink::PilotWireThermostatControlRoom::turnComfortHeaters()
{
    oplink::QspStateToWatchList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(auto i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspStateToWatch ms{heatersCategory->at(i)};
        pwmHeater(ms->observableName(),ms->propertyName(),oplink::CommandArgs::COMFORT);
    }
}
