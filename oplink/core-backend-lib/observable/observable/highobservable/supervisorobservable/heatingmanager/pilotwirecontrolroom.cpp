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

#include "pilotwirecontrolroom.h"
#include "heatingmanager.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/grouptowatch.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/statetowatchlist.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/statetowatch.h"
#include "observable/values.h"
#include "logger/pflog.h"

oplink::PilotWireControlRoom::PilotWireControlRoom(oplink::SupervisorObservable& manager,bool wod):
    oplink::GroupToWatchAlgorithm{manager},
    m_wod{wod},
    m_pd{false},
    m_roomClosed{false},
    m_last_regulation_order{oplink::Values::PW_MODE_STOP}
{}

oplink::PilotWireControlRoom::~PilotWireControlRoom()
{

}

void oplink::PilotWireControlRoom::orderForHeaters(const QString &order)
{
    oplink::QspStateToWatchList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    pfInfo2(manager().logChannel()) << tr("%1 nouvelle consigne %2 pour la pièce %3").arg(manager().name(), order, group()->groupName());
    m_last_regulation_order = Values::convertStr2pwm(order);
    for(auto i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspStateToWatch ms{heatersCategory->at(i)};

        pwmHeater(ms->observableName(),ms->propertyName(),order);
    }
}

void oplink::PilotWireControlRoom::subscribe()
{  
    oplink::GroupToWatch *myRoom{group()};

    // subscribe to all objects monitored by the group
    //------------------------------------------------

    // heaters
    subscribeToCategory(HeatingManager::heaterCategory(),
                        myRoom);
    if (wod())
    {
        // w sensors
        subscribeToCategory(HeatingManager::windowSensorCategory(),
                            myRoom);
    }
}

void oplink::PilotWireControlRoom::unsubscribe()
{
    oplink::GroupToWatch *myRoom{group()};

    // unsubscribe to all objects monitored by the group
    //------------------------------------------------

    // heaters
    unsubscribeToCategory(HeatingManager::heaterCategory(),
                          myRoom);
    if (wod())
    {
        // w sensors
        unsubscribeToCategory(HeatingManager::windowSensorCategory(),
                              myRoom);
    }
}

void oplink::PilotWireControlRoom::onStateChange(oplink::ObservableName observableName,
                                         oplink::PropertyName propertyName,
                                         QVariant propertyValue)
{
    QString reverseInput{observableName+propertyName};
    QString category{group()->reverseLookUp(reverseInput)};

    if (!category.isEmpty())
    {
        if (HeatingManager::heaterCategory() == category)
        {
            onStateChangeFromHeaters(observableName,propertyName,propertyValue);
        }
        else if (HeatingManager::windowSensorCategory() == category)
        {
            onStateChangeFromWindowSensors(observableName,propertyName,propertyValue);
        }
        else if (HeatingManager::temperatureSensorCategory() == category)
        {
            onStateChangeFromTemperatureSensors(observableName,propertyName,propertyValue);
        }
        else
        {
            onStateChangeFromUnknownCategory(observableName,propertyName,propertyValue);
        }
    }
}

void oplink::PilotWireControlRoom::onStateChangeFromHeaters(const oplink::ObservableName&  observableName,
                                                            const oplink::PropertyName& propertyName,
                                                            QVariant propertyValue)
{
    quint8 val;

    val = propertyValue.toUInt();

    pfInfo2(manager().logChannel()) << tr("%1 pièce %2 changement d'état observé : radiateur %3, status %4").arg(manager().name(), group()->groupName(),observableName,Values::convertPWM2str(val));

    if (wod() && !roomClosed())
    {
        if (val != Values::PW_MODE_STOP)
        {
            // Force stop, windows are open !
            pfInfo2(manager().logChannel()) << tr("%1 pièce %2, fenêtre(s) ouverte(s), %3 commandé à OFF").arg(manager().name(),group()->groupName(),observableName);
            pwmHeater(observableName,propertyName,CommandArgs::OFF);
        }
    }
    else if (lastRegulationOrder() != val)
    {
        // Force to last order
        QString lastOrd{Values::convertPWM2str(lastRegulationOrder())};

        pfInfo2(manager().logChannel()) << tr("%1 pièce %2, fenêtre(s) fermée(s), %3 restauré à %4").arg(manager().name(),group()->groupName(),observableName,lastOrd);
        pwmHeater(observableName,propertyName,lastOrd);
    }
}

void oplink::PilotWireControlRoom::onStateChangeFromWindowSensors(const oplink::ObservableName& observableName,
                                                          const oplink::PropertyName& propertyName,
                                                          QVariant propertyValue)
{
    Q_UNUSED(propertyName)
    HeatingManager& heatingManager{dynamic_cast<HeatingManager&>(manager())};

    pfInfo2(manager().logChannel()) << tr("%1 pièce %2 changement d'état observé : capteur ouverture fenêtre %3, status ").arg(manager().name(),group()->groupName(),observableName) << propertyValue.toBool();

    m_roomClosed = group()->allTrue(HeatingManager::windowSensorCategory());
    if (heatingManager.windowSensorState(group()->groupName(),m_roomClosed))
    {
        // decide on the action to take only if the manager is activated
        //--------------------------------------------------------------
        if (m_roomClosed)
        {
            QString lastOrd{Values::convertPWM2str(lastRegulationOrder())};
            pfInfo2(manager().logChannel()) << tr("%1 pièce %2, fenêtre(s) fermée(s), restaurer les radiateurs à %3").arg(manager().name(),group()->groupName(),lastOrd);
            turnLastOrderHeaters();
        }
        else
        {
            pfInfo2(manager().logChannel()) << tr("%1 pièce %2, fenêtre(s) ouverte(s), arrêter tous les radiateurs").arg(manager().name(),group()->groupName());
            turnOffHeaters();
        }
    }
}

void oplink::PilotWireControlRoom::onStateChangeFromTemperatureSensors(const oplink::ObservableName& observableName,
                                                               const oplink::PropertyName& propertyName,
                                                               QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
}

void oplink::PilotWireControlRoom::onStateChangeFromUnknownCategory(const oplink::ObservableName& observableName,
                                                            const oplink::PropertyName& propertyName,
                                                            QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
}

void oplink::PilotWireControlRoom::pwmHeater(const QString &oname,const QString &pname,const QString &pwm)
{
    QString format("%1 %2 %3 %4");
    oplink::StrOrder order(format.arg(oplink::CommandNames::SET,oname,pname,pwm));

    observableService()->submitOrder(order);
}

void oplink::PilotWireControlRoom::turnLastOrderHeaters()
{
    oplink::QspStateToWatchList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    pfDebug4(manager().logChannel()) << manager().name() << " room " << group()->groupName() << " send the last instruction back to all radiators";

    for(auto i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspStateToWatch ms{heatersCategory->at(i)};
        QString lastOrder{Values::convertPWM2str(lastRegulationOrder())};

        pfDebug4(manager().logChannel()) << ms->observableName() << " " << ms->propertyName() << " send " << lastOrder;
        pwmHeater(ms->observableName(),ms->propertyName(),lastOrder);
    }
}

void oplink::PilotWireControlRoom::turnOffHeaters()
{
    oplink::QspStateToWatchList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(auto i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspStateToWatch ms{heatersCategory->at(i)};
        pwmHeater(ms->observableName(),ms->propertyName(),oplink::CommandArgs::OFF);
    }
}
