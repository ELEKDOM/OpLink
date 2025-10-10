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


#include "heatingmanager/heatingmanagerloader.h"
#include "heatingmanager/heatingmanager.h"
#include "heatingmanager/pilotwirecontrolroom.h"
#include "heatingmanager/pilotwirethermostatcontrolroom.h"
#include "abstract_virtualequipementset/virtualequipmentset.h"
#include "observable/property/propertyid.h"
#include "observable/highobservable/monitor/grouptowatch.h"
#include "observable/highobservable/monitor/statetowatch.h"
#include "scheduler/schedulerbuilder.h"
#include "heatingmanagersetlogchannel.h"

using namespace elekdom::plugframe::core::scheduler;
using namespace elekdom::oplink;
using namespace elekdom::oplink::core;
using namespace elekdom::oplink::heatingmanager;

HeatingManagerLoader::HeatingManagerLoader(virtualequipmentset::bundle::VirtualEquipmentSet *veSet):
    core::virtualequipment::VirtualEquipmentLoader{veSet},
    m_newHeatingManager{nullptr},
    m_schedulerBuilder{new SchedulerBuilder(s_HeatingManagerSetLogChannel)}
{}

HeatingManagerLoader::~HeatingManagerLoader()
{

}

void HeatingManagerLoader::browseBegin()
{

}

void HeatingManagerLoader::browseEnd()
{

}

bool HeatingManagerLoader::heatingManagerDeclarationBegin(const QString& observableName,
                                                          const QString& modelName,
                                                          const QString& title,
                                                          const QString& localisation,
                                                          HeatingManagerLoaderHook::ControlType controlType,
                                                          int confId)
{
    bool ret{false};
    Q_UNUSED(title)

    // Build a new heatingManager
    //----------------------------
    m_ctrT = controlType;
    m_newHeatingManager = createHeatingManager();

    if (m_newHeatingManager!= nullptr)
    {
        ret = true;

        newly(m_newHeatingManager); // holds the observable

        // build virtualequipment's mandatory properties
        buildMandatoryProperties(observableName,modelName,localisation,confId);

        // Heating manager's specific property
        addProperty(observable::PropertyId::P_ORDER, QVariant::String);
    }

    return ret;
}

bool HeatingManagerLoader::heatingManagerDeclarationEnd()
{
    if(m_newHeatingManager!= nullptr)
    {
        m_newHeatingManager->init(veSet()->observableService());
    }

    return true;
}

bool HeatingManagerLoader::controlDeclarationBegin(const QString &mode,
                                                   bool windowOpeningDetection,
                                                   bool presenceDetection,
                                                   double threshold,
                                                   double maxTemp)
{
    m_wo_detection = windowOpeningDetection;
    m_p_detection = presenceDetection;
    m_max_temp = maxTemp;
    m_threshold = threshold;

    modeValue(mode);

    return true;
}

bool HeatingManagerLoader::controlDeclarationEnd()
{
    return true;
}

SchedulerElementHook &HeatingManagerLoader::schedulerDeclarationBegin()
{
    return *m_schedulerBuilder;
}

bool HeatingManagerLoader::schedulerDeclarationEnd()
{
    bool ret{true};

    m_newHeatingManager->setScheduler(m_schedulerBuilder->newly());
    return ret;
}

bool HeatingManagerLoader::roomsDeclarationBegin()
{
    bool ret{true};

    return true;
}

bool HeatingManagerLoader::roomsDeclarationEnd()
{
    bool ret{true};

    return true;
}

bool HeatingManagerLoader::roomDeclarationBegin(const QString &roomName)
{
    bool ret;

    ret = !roomName.isEmpty();
    if (ret)
    {
        observable::monitoring::QspMonitoredGroupAlgorithm ptrAlgo{createControlRoom()};
        ret = !ptrAlgo.isNull();
        if (ret)
        {
            m_monitoredRoom.reset(new observable::monitoring::GroupToWatch{ptrAlgo});
            m_monitoredRoom->groupName(roomName);
        }
    }
    return ret;
}

bool HeatingManagerLoader::roomDeclarationEnd()
{
    bool ret;

    ret = !m_monitoredRoom.isNull();
    if (ret)
    {
        m_newHeatingManager->addMonitoredObservableGroup(m_monitoredRoom->groupName(),
                                                         m_monitoredRoom);
        buildRoomProperties(m_monitoredRoom->groupName(), m_monitoredRoom);
    }

    return ret;
}

bool HeatingManagerLoader::heatersDeclarationBegin()
{
    bool ret{true};

    m_monitoredRoom->addCategory(heatingmanager::HeatingManager::heaterCategory());

    return ret;
}

bool HeatingManagerLoader::heatersDeclarationEnd()
{
    bool ret{true};

    return ret;
}

bool HeatingManagerLoader::heaterRefDeclaration(const QString &heaterName, const QString &heaterPropertyName)
{
    bool ret;

    ret = !heaterName.isEmpty() && !heaterPropertyName.isEmpty();
    if (ret)
    {
        observable::monitoring::QspMonitoredState monitoredState{createStateToWatch(heaterName,heaterPropertyName)};

        m_monitoredRoom->addMonitoredState(heatingmanager::HeatingManager::heaterCategory(),
                                           monitoredState);
    }
    return ret;
}

bool HeatingManagerLoader::windowSensorsDeclarationBegin()
{
    bool ret{m_wo_detection};

    if (ret)
    {
        m_monitoredRoom->addCategory(heatingmanager::HeatingManager::windowSensorCategory());
    }

    return ret;
}

bool HeatingManagerLoader::windowSensorsDeclarationEnd()
{
    bool ret{true};

    return ret;
}

bool HeatingManagerLoader::windowSensorRefDeclaration(const QString& windowSensorName,
                                                      const QString& windowSensorPropertyName)
{
    bool ret{m_wo_detection};

    if (ret)
    {
        ret = !windowSensorName.isEmpty() && !windowSensorPropertyName.isEmpty();
        if (ret)
        {
            observable::monitoring::QspMonitoredState monitoredState{createStateToWatch(windowSensorName,windowSensorPropertyName)};

            m_monitoredRoom->addMonitoredState(heatingmanager::HeatingManager::windowSensorCategory(),
                                               monitoredState);
        }
    }

    return ret;
}

bool HeatingManagerLoader::temperatureSensorsDeclarationBegin()
{
    bool ret{m_ctrT == ControlType::PWT};

    if (ret)
    {
        m_monitoredRoom->addCategory(heatingmanager::HeatingManager::temperatureSensorCategory());
    }

    return ret;
}

bool HeatingManagerLoader::temperatureSensorsDeclarationEnd()
{
    bool ret{false};

    return ret;
}

bool HeatingManagerLoader::temperatureSensorRefDeclaration(const QString &temperatureSensorName, const QString &temperatureSensorPropertyName)
{
    bool ret{m_ctrT == ControlType::PWT};

    if (ret)
    {
        ret = !temperatureSensorName.isEmpty() && !temperatureSensorPropertyName.isEmpty();
        if (ret)
        {
            observable::monitoring::QspMonitoredState monitoredState{createStateToWatch(temperatureSensorName,temperatureSensorPropertyName)};

            m_monitoredRoom->addMonitoredState(heatingmanager::HeatingManager::temperatureSensorCategory(),
                                               monitoredState);
        }
    }

    return ret;
}

virtualequipment::VirtualEquipmentLoaderHook &HeatingManagerLoader::loaderHook()
{
    return *this;
}

HeatingManager *HeatingManagerLoader::createHeatingManager()
{
    return new HeatingManager;
}

PilotWireControlRoom *HeatingManagerLoader::createControlRoom()
{
    heatingmanager::PilotWireControlRoom *ret{nullptr};

    if (ControlType::PW == m_ctrT)
    {
        ret = new heatingmanager::PilotWireControlRoom{*m_newHeatingManager,
                                                       m_wo_detection,
                                                       m_p_detection};
    }
    else if (ControlType::PWT == m_ctrT)
    {
        ret = new heatingmanager::PilotWireThermostatControlRoom{*m_newHeatingManager,
                                                                 m_wo_detection,
                                                                 m_p_detection,
                                                                 m_max_temp,
                                                                 m_threshold};
    }

    return ret;
}

void HeatingManagerLoader::buildRoomProperties(const QString &roomName,
                                               observable::monitoring::QspMonitoredObservableGroup roomGroup)
{
    addGroupProperty(roomName,observable::PropertyId::P_DEROGATED,QVariant::Bool);
    addGroupProperty(roomName,observable::PropertyId::P_DEROGATED_ORDER,QVariant::String);
    if (!roomGroup->isCategoryEmpty(heatingmanager::HeatingManager::windowSensorCategory()))
    {
        addGroupProperty(roomName,observable::PropertyId::P_WCLOSED,QVariant::Bool);
    }
    if (!roomGroup->isCategoryEmpty(heatingmanager::HeatingManager::temperatureSensorCategory()))
    {
        addGroupProperty(roomName,observable::PropertyId::P_TEMPERATURE,QVariant::Double);
    }
}
