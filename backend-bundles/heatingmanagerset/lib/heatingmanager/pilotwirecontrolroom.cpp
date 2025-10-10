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
#include "observable/highobservable/monitor/grouptowatch.h"
#include "observable/highobservable/monitor/statetowatchlist.h"
#include "observable/highobservable/monitor/statetowatch.h"
#include "observable/values.h"
#include "command/command-names.h"

using namespace elekdom::oplink::heatingmanager;
using namespace elekdom::oplink::core;

PilotWireControlRoom::PilotWireControlRoom(core::observable::SupervisorObservable& manager,bool wod,bool pd):
    core::observable::monitoring::GroupToWatchAlgorithm{manager},
    m_wod{wod},
    m_pd{pd},
    m_roomClosed{true}
{}

PilotWireControlRoom::~PilotWireControlRoom()
{

}

void PilotWireControlRoom::orderForHeaters(const QString &order)
{
    observable::monitoring::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(int i = 0; i < heatersCategory->size(); i++)
    {
        observable::monitoring::QspMonitoredState ms{heatersCategory->at(i)};

        pwmHeater(ms->observableName(),ms->propertyName(),order);
    }
}

void PilotWireControlRoom::initAlgo()
{  
    observable::monitoring::GroupToWatch *myRoom{group()};

    // subscribe to all objects monitored by the group
    //------------------------------------------------

    // heaters
    subscribeToCategory(HeatingManager::heaterCategory(),
                        myRoom,
                        observableService());
    if (wod())
    {
        // w sensors
        subscribeToCategory(HeatingManager::windowSensorCategory(),
                            myRoom,
                            observableService());
    }
}

void PilotWireControlRoom::onStateChange(const core::observable::ObservableName& observableName,
                                         const core::observable::PropertyName& propertyName,
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

void PilotWireControlRoom::onStateChangeFromHeaters(const core::observable::ObservableName&  observableName,
                                                    const core::observable::PropertyName& propertyName,
                                                    QVariant propertyValue)
{
    quint8 val;

    val = propertyValue.toUInt();
    if (m_wod && !m_roomClosed)
    {
        if (val != observable::Values::PW_MODE_STOP)
        {
            // Force stop, windows are open !
            pwmHeater(observableName,propertyName,command::CommandArgs::OFF);
        }
    }
    else
    {
        HeatingManager& heatingManager{dynamic_cast<HeatingManager&>(manager())};

        heatingManager.heaterState(group()->groupName(),convertPWM2str(val)) ;
    }
}

void PilotWireControlRoom::onStateChangeFromWindowSensors(const core::observable::ObservableName& observableName,
                                                          const core::observable::PropertyName& propertyName,
                                                          QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
    HeatingManager& heatingManager{dynamic_cast<HeatingManager&>(manager())};

    m_roomClosed = group()->allTrue(HeatingManager::windowSensorCategory());
    if (heatingManager.windowSensorState(group()->groupName(),m_roomClosed))
    {
        // decide on the action to take only if the manager is activated
        //--------------------------------------------------------------
        if (m_roomClosed)
        {
            turnLastOrderHeaters();
        }
        else
        {
            turnOffHeaters();
        }
    }
}

void PilotWireControlRoom::onStateChangeFromTemperatureSensors(const core::observable::ObservableName& observableName,
                                                               const core::observable::PropertyName& propertyName,
                                                               QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
}

void PilotWireControlRoom::onStateChangeFromUnknownCategory(const core::observable::ObservableName& observableName,
                                                            const core::observable::PropertyName& propertyName,
                                                            QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
}

void PilotWireControlRoom::pwmHeater(const QString &oname,const QString &pname,const QString &pwm)
{
    QString format("%1 %2 %3 %4");
    command::StrOrder order(format.arg(command::CommandNames::SET,oname,pname,pwm));

    observableService()->submitOrder(order);
}

void PilotWireControlRoom::turnLastOrderHeaters()
{
    observable::monitoring::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(int i = 0; i < heatersCategory->size(); i++)
    {
        observable::monitoring::QspMonitoredState ms{heatersCategory->at(i)};
        QVariant lastOrder{ms->value()};

        if (lastOrder.isValid())
        {
            quint8 val;
            QString strVal;

            val = lastOrder.toUInt();
            strVal = convertPWM2str(val);
            pwmHeater(ms->observableName(),ms->propertyName(),strVal);
        }
    }
}

void PilotWireControlRoom::turnComfortHeaters()
{
    observable::monitoring::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(int i = 0; i < heatersCategory->size(); i++)
    {
        observable::monitoring::QspMonitoredState ms{heatersCategory->at(i)};
        pwmHeater(ms->observableName(),ms->propertyName(),command::CommandArgs::COMFORT);
    }
}

void PilotWireControlRoom::turnOffHeaters()
{
    observable::monitoring::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(int i = 0; i < heatersCategory->size(); i++)
    {
        observable::monitoring::QspMonitoredState ms{heatersCategory->at(i)};
        pwmHeater(ms->observableName(),ms->propertyName(),command::CommandArgs::OFF);
    }
}

QString PilotWireControlRoom::convertPWM2str(quint8 pwm)
{
    QString ret;

    if (pwm == observable::Values::PW_MODE_COMFORT)
    {
        ret = command::CommandArgs::COMFORT;
    }
    else if(pwm == observable::Values::PW_MODE_COMFORT_1)
    {
        ret = command::CommandArgs::COMFORT_1;
    }
    else if(pwm == observable::Values::PW_MODE_COMFORT_2)
    {
        ret = command::CommandArgs::COMFORT_2;
    }
    else if(pwm == observable::Values::PW_MODE_ECO)
    {
        ret = command::CommandArgs::ECO;
    }
    else if(pwm == observable::Values::PW_MODE_ANTI_FREEZE)
    {
        ret = command::CommandArgs::NOFROST;
    }
    else
    {
        ret = command::CommandArgs::OFF;
    }

    return ret;
}
