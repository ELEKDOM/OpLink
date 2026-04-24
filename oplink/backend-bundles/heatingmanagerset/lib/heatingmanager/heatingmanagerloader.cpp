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

#include "heatingmanagerloader.h"
#include "abstract_virtualequipementset/virtualequipmentset.h"
#include "observable/heatingmanagermodelnames.h"
#include "observable/observablelogchannel.h"

HeatingManagerLoader::HeatingManagerLoader(oplink::VirtualEquipmentSet *veSet):
    oplink::VirtualEquipmentLoader{veSet},
    m_newHeatingManagerBuilderArgs{nullptr}
{
    m_schedulerBuilder.reset(new plugframe::SchedulerBuilder(s_ObservableLogChannel));  // logged to "Observable" channel !
}

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
                                                          const QString& title,
                                                          const QString& localisation,
                                                          HeatingManagerLoaderHook::ControlType controlType,
                                                          bool activated)
{
    bool ret{false};
    QString modelName;
    Q_UNUSED(title)

    // Build a new heatingManagerBuilderArgs (HeatingManagers are built by an observable model)
    //-----------------------------------------------------------------------------------------
    m_ctrT = controlType;
    if (ControlType::PWT == controlType)
    {
        modelName = oplink::HeatingManagerModelNames::pilotWireThermostatModelName();
    }
    else if (ControlType::PW == controlType)
    {
        modelName = oplink::HeatingManagerModelNames::pilotWireModelName();
    }
    m_newHeatingManagerBuilderArgs = createHeatingManagerBuilderArgs(observableName,
                                                                     modelName,
                                                                     localisation,
                                                                     activated,
                                                                     controlType);

    builderArgs(m_newHeatingManagerBuilderArgs); // holds the builderargs
    ret = m_newHeatingManagerBuilderArgs!= nullptr;

    return ret;
}

bool HeatingManagerLoader::heatingManagerDeclarationEnd()
{
    return true;
}

bool HeatingManagerLoader::controlDeclarationBegin(const QString& setPointValue,
                                                   double threshold,
                                                   double maxTemp)
{
    m_newHeatingManagerBuilderArgs->m_max_temp = maxTemp;
    m_newHeatingManagerBuilderArgs->m_threshold = threshold;
    if (HeatingManagerLoaderHook::scheduledSetPoint() == setPointValue)
    {
        m_newHeatingManagerBuilderArgs->m_setPointScheduled = true;
    }
    else
    {
        m_newHeatingManagerBuilderArgs->m_setPoint = setPointValue;
    }

    return true;
}

bool HeatingManagerLoader::controlDeclarationEnd()
{
    return true;
}

plugframe::SchedulerElementHook &HeatingManagerLoader::schedulerDeclarationBegin(const QString& xmlText)
{
    m_newHeatingManagerBuilderArgs->m_schedulXmlText = xmlText;
    return *m_schedulerBuilder;
}

bool HeatingManagerLoader::schedulerDeclarationEnd()
{
    bool ret{true};

    m_newHeatingManagerBuilderArgs->m_schedul.reset(m_schedulerBuilder->newly());
    return ret;
}

bool HeatingManagerLoader::roomsDeclarationBegin()
{
    bool ret{true};

    return ret;
}

bool HeatingManagerLoader::roomsDeclarationEnd()
{
    bool ret{true};

    return ret;
}

bool HeatingManagerLoader::roomDeclarationBegin(const QString& roomName,
                                                bool windowOpeningDetection)
{
    bool ret;

    ret = !roomName.isEmpty();
    if (ret)
    {
        m_curRoomDeclaration.reset(new oplink::HeatedRoomBuilderArgs{roomName,windowOpeningDetection});
        ret = !m_curRoomDeclaration.isNull();
    }
    return ret;
}

bool HeatingManagerLoader::roomDeclarationEnd()
{
    bool ret;

    ret = !m_curRoomDeclaration.isNull();
    if (ret)
    {
        m_newHeatingManagerBuilderArgs->m_rooms.append(m_curRoomDeclaration);
    }

    return ret;
}

bool HeatingManagerLoader::heatersDeclarationBegin()
{
    bool ret{true};

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
        oplink::QspPropertyRefBuilderArgs propertyRef{createPropertyRef(heaterName,heaterPropertyName)};
        m_curRoomDeclaration->m_heaters.append(propertyRef);
    }
    return ret;
}

bool HeatingManagerLoader::windowSensorsDeclarationBegin()
{
    bool ret{true};

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
    bool ret{!windowSensorName.isEmpty() && !windowSensorPropertyName.isEmpty()};

    if (ret)
    {
        oplink::QspPropertyRefBuilderArgs propertyRef{createPropertyRef(windowSensorName,windowSensorPropertyName)};
        m_curRoomDeclaration->m_windowSensors.append(propertyRef);
    }

    return ret;
}

bool HeatingManagerLoader::temperatureSensorsDeclarationBegin()
{
    bool ret{true};

    return ret;
}

bool HeatingManagerLoader::temperatureSensorsDeclarationEnd()
{
    bool ret{false};

    return ret;
}

bool HeatingManagerLoader::temperatureSensorRefDeclaration(const QString &temperatureSensorName,
                                                           const QString &temperatureSensorPropertyName)
{
    bool ret{!temperatureSensorName.isEmpty() && !temperatureSensorPropertyName.isEmpty()};

    if (ret)
    {
        oplink::QspPropertyRefBuilderArgs propertyRef{createPropertyRef(temperatureSensorName,temperatureSensorPropertyName)};
        m_curRoomDeclaration->m_tempSensors.append(propertyRef);
    }

    return ret;
}

oplink::HighObservableLoaderHook &HeatingManagerLoader::loaderHook()
{
    return *this;
}

oplink::HeatingManagerBuilderArgs *HeatingManagerLoader::createHeatingManagerBuilderArgs(const QString& observableName,
                                                                                         const QString& modelName,
                                                                                         const QString& localisation,
                                                                                         bool activated,
                                                                                         HeatingManagerLoaderHook::ControlType controlType)
{
    return new oplink::HeatingManagerBuilderArgs{observableName,
                                                 modelName,
                                                 localisation,
                                                 controlType,
                                                 activated};
}

