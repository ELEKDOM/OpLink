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

PilotWireControlRoom::PilotWireControlRoom(oplink::SupervisorObservable& manager,bool wod,bool pd):
    oplink::GroupToWatchAlgorithm{manager},
    m_wod{wod},
    m_pd{pd},
    m_roomClosed{true}
{}

PilotWireControlRoom::~PilotWireControlRoom()
{

}

void PilotWireControlRoom::orderForHeaters(const QString &order)
{
    oplink::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(int i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspMonitoredState ms{heatersCategory->at(i)};

        pwmHeater(ms->observableName(),ms->propertyName(),order);
    }
}

void PilotWireControlRoom::initAlgo()
{  
    oplink::GroupToWatch *myRoom{group()};

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

void PilotWireControlRoom::onStateChange(oplink::ObservableName observableName,
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

void PilotWireControlRoom::onStateChangeFromHeaters(const oplink::ObservableName&  observableName,
                                                    const oplink::PropertyName& propertyName,
                                                    QVariant propertyValue)
{
    quint8 val;

    val = propertyValue.toUInt();
    if (m_wod && !m_roomClosed)
    {
        if (val != oplink::Values::PW_MODE_STOP)
        {
            // Force stop, windows are open !
            pwmHeater(observableName,propertyName,oplink::CommandArgs::OFF);
        }
    }
    else
    {
        HeatingManager& heatingManager{dynamic_cast<HeatingManager&>(manager())};

        heatingManager.heaterState(group()->groupName(),convertPWM2str(val)) ;
    }
}

void PilotWireControlRoom::onStateChangeFromWindowSensors(const oplink::ObservableName& observableName,
                                                          const oplink::PropertyName& propertyName,
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

void PilotWireControlRoom::onStateChangeFromTemperatureSensors(const oplink::ObservableName& observableName,
                                                               const oplink::PropertyName& propertyName,
                                                               QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
}

void PilotWireControlRoom::onStateChangeFromUnknownCategory(const oplink::ObservableName& observableName,
                                                            const oplink::PropertyName& propertyName,
                                                            QVariant propertyValue)
{
    Q_UNUSED(observableName)
    Q_UNUSED(propertyName)
    Q_UNUSED(propertyValue)
}

void PilotWireControlRoom::pwmHeater(const QString &oname,const QString &pname,const QString &pwm)
{
    QString format("%1 %2 %3 %4");
    oplink::StrOrder order(format.arg(oplink::CommandNames::SET,oname,pname,pwm));

    observableService()->submitOrder(order);
}

void PilotWireControlRoom::turnLastOrderHeaters()
{
    oplink::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(qsizetype i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspMonitoredState ms{heatersCategory->at(i)};
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
    oplink::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(qsizetype i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspMonitoredState ms{heatersCategory->at(i)};
        pwmHeater(ms->observableName(),ms->propertyName(),oplink::CommandArgs::COMFORT);
    }
}

void PilotWireControlRoom::turnOffHeaters()
{
    oplink::QspMonitoredStateList heatersCategory(group()->category(HeatingManager::heaterCategory()));

    for(qsizetype i = 0; i < heatersCategory->size(); i++)
    {
        oplink::QspMonitoredState ms{heatersCategory->at(i)};
        pwmHeater(ms->observableName(),ms->propertyName(),oplink::CommandArgs::OFF);
    }
}

QString PilotWireControlRoom::convertPWM2str(quint8 pwm)
{
    QString ret;

    if (pwm == oplink::Values::PW_MODE_COMFORT)
    {
        ret = oplink::CommandArgs::COMFORT;
    }
    else if(pwm == oplink::Values::PW_MODE_COMFORT_1)
    {
        ret = oplink::CommandArgs::COMFORT_1;
    }
    else if(pwm == oplink::Values::PW_MODE_COMFORT_2)
    {
        ret = oplink::CommandArgs::COMFORT_2;
    }
    else if(pwm == oplink::Values::PW_MODE_ECO)
    {
        ret = oplink::CommandArgs::ECO;
    }
    else if(pwm == oplink::Values::PW_MODE_ANTI_FREEZE)
    {
        ret = oplink::CommandArgs::NOFROST;
    }
    else
    {
        ret = oplink::CommandArgs::OFF;
    }

    return ret;
}
