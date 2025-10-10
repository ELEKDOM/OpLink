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


#include "heatingmanagerconfdocument.h"
#include "heatingmanagerloaderhook.h"
#include "scheduler/schedulerelement.h"

using namespace elekdom::oplink::core::heatingmanager;

HeatingManagerConfDocument::HeatingManagerConfDocument(HeatingManagerLoaderHook& browserHook):
    virtualequipment::VirtualEquipmentConfDocument{browserHook}
{

}

HeatingManagerConfDocument::~HeatingManagerConfDocument()
{

}

QString HeatingManagerConfDocument::rootNodeName()
{
    return heatingManagerTag();
}

HeatingManagerLoaderHook& HeatingManagerConfDocument::hook()
{
    return dynamic_cast<HeatingManagerLoaderHook&>(browserHook());
}

bool HeatingManagerConfDocument::_browse()
{
    bool ret{false};
    QDomElement rootElem{documentElement()};

    if (rootElem.tagName() == heatingManagerTag())
    {
        ret = extractDataFromHeatingManagerElement(rootElem);
    }

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromHeatingManagerElement(QDomElement& hmElem)
{
    bool ret{false};
    QString observableName,modelName,title,localisation,controlTypeAttr,idAttr;
    HeatingManagerLoaderHook::ControlType controlType{HeatingManagerLoaderHook::ControlType::Unknow};
    int confId;

    observableName = hmElem.attribute(nameAttr());
    modelName = hmElem.attribute(modelnameAttr());
    title = hmElem.attribute(titleAttr());
    localisation = hmElem.attribute(localisationAttr());
    idAttr=hmElem.attribute(confidAttr());
    confId = idAttr.toInt();
    controlTypeAttr = hmElem.attribute(controlAttr());
    if (controlType_pw() == controlTypeAttr)
    {
        controlType = HeatingManagerLoaderHook::ControlType::PW;
    }
    else  if (controlType_pwt() == controlTypeAttr)
    {
        controlType = HeatingManagerLoaderHook::ControlType::PWT;
    }

    ret = hook().heatingManagerDeclarationBegin(observableName,
                                                modelName,
                                                title,
                                                localisation,
                                                controlType,
                                                confId);
    if (ret)
    {
        // Control part
        //-------------
        if (controlType != HeatingManagerLoaderHook::ControlType::Unknow)
        {
            ret = extractDataFromControlElement(hmElem,observableName,controlType);

            // Rooms part
            //-----------
            if (ret)
            {
                ret = extractDataFromRoomsElement(hmElem);
            }
        }
    }

    hook().heatingManagerDeclarationEnd();

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromControlElement(QDomElement &hmElem,
                                                               const QString& observableName,
                                                               HeatingManagerLoaderHook::ControlType ctrT)
{
    bool ret{false};
    QString tagName;
    QDomNodeList descendants;

    if (ctrT == HeatingManagerLoaderHook::ControlType::PW)
    {
        tagName = pwControlTag();
    }
    else if (ctrT == HeatingManagerLoaderHook::ControlType::PWT)
    {
        tagName = pwtControlTag();
    }

    descendants = hmElem.elementsByTagName(tagName);
    if (descendants.size() == 1) // only one control element expected !
    {
        QDomElement controlElem{descendants.at(0).toElement()};
        QString modeValue;
        bool wod,pd;
        double threshold{0.0},max_temp{0.0};

        wod = controlElem.attribute(windowOpeningDetectionAttr()) == detection_on();
        pd = controlElem.attribute(presenceDetectionAttr()) == detection_on();
        modeValue = controlElem.attribute(modeAttr());

        if (ctrT == HeatingManagerLoaderHook::ControlType::PWT)
        {
            QString tmp;

            tmp = controlElem.attribute(thresholdAttr()); // only for pwt control
            if (!tmp.isEmpty())
            {
                threshold = tmp.toDouble();
            }
            tmp = controlElem.attribute(maxTempdAttr()); // only for pwt control
            if (!tmp.isEmpty())
            {
                max_temp = tmp.toDouble();
            }
        }

        ret = hook().controlDeclarationBegin(modeValue,wod,pd,threshold,max_temp);
        if (ret)
        {
            ret = extractScheduler(controlElem,observableName);
        }
        hook().controlDeclarationEnd();
    }

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromRoomsElement(QDomElement &hmElem)
{
    bool ret{true};
    QDomNodeList descendants{hmElem.elementsByTagName(roomsTag())};

    hook().roomsDeclarationBegin();

    if (descendants.size() == 1) // only one rooms element expected
    {
        QDomElement roomsElem{descendants.at(0).toElement()};
        QDomNodeList roomList{roomsElem.elementsByTagName(roomTag())};

        for (int i = 0; i < roomList.size() && ret; i++)
        {
            QDomElement roomElem{roomList.at(i).toElement()};

            ret = extractDataFromRoomElement(roomElem);
        }
    }

    hook().roomsDeclarationEnd();

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromRoomElement(QDomElement &roomElem)
{
    bool ret;
    QString roomName{roomElem.attribute(nameAttr())};

    ret = hook().roomDeclarationBegin(roomName);
    if (ret)
    {
        ret = extractDataFromHeatersElement(roomElem);
        if (ret)
        {
            ret = extractDataFromWindowSensorsElement(roomElem);
            if (ret)
            {
                ret = extractDataFromTemperatureSensorsElement(roomElem);
            }
        }
    }
    hook().roomDeclarationEnd();

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromHeatersElement(QDomElement &roomElem)
{
    bool ret{true};
    QDomNodeList descendants{roomElem.elementsByTagName(heatersTag())}; // only one heaters element expected

    hook().heatersDeclarationBegin();

    if (descendants.size() == 1)
    {
        QDomElement heatersElem{descendants.at(0).toElement()};
        QDomNodeList heaterRefList{heatersElem.elementsByTagName(heaterRefTag())};

        for (int i = 0; i < heaterRefList.size() && ret; i++)
        {
            QDomElement heaterRefElem{heaterRefList.at(i).toElement()};
            QString heaterName{heaterRefElem.attribute(nameAttr())};
            QString heaterPropertyName{heaterRefElem.attribute(propertyAttr())};

            ret = hook().heaterRefDeclaration(heaterName,heaterPropertyName);
        }
    }

    hook().heatersDeclarationEnd();

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromWindowSensorsElement(QDomElement &roomElem)
{
    bool ret{true};
    QDomNodeList descendants{roomElem.elementsByTagName(windowSensorsTag())}; // only one optionnal windosensors element expected

    hook().windowSensorsDeclarationBegin();

    if (descendants.size() == 1)
    {
        QDomElement windowSensorsElem{descendants.at(0).toElement()};
        QDomNodeList windowSensorRefList{windowSensorsElem.elementsByTagName(windowSensorRefTag())};

        for (int i = 0; i < windowSensorRefList.size() && ret; i++)
        {
            QDomElement windowSensorRefElem{windowSensorRefList.at(i).toElement()};
            QString windowSensorName{windowSensorRefElem.attribute(nameAttr())};
            QString windowSensorPropertyName{windowSensorRefElem.attribute(propertyAttr())};

            ret = hook().windowSensorRefDeclaration(windowSensorName,windowSensorPropertyName);
        }
    }

    hook().windowSensorsDeclarationEnd();

    return ret;
}

bool HeatingManagerConfDocument::extractDataFromTemperatureSensorsElement(QDomElement &roomElem)
{
    bool ret{true};
    QDomNodeList descendants{roomElem.elementsByTagName(temperatureSensorsTag())}; // only one tempsensors element expected

    hook().temperatureSensorsDeclarationBegin();

    if (descendants.size() == 1)
    {
        QDomElement temperatureSensorsElem{descendants.at(0).toElement()};
        QDomNodeList temperatureSensorRefList{temperatureSensorsElem.elementsByTagName(temperatureSensorRefTag())};

        for (int i = 0; i < temperatureSensorRefList.size() && ret; i++)
        {
            QDomElement temperatureSensorRefElem{temperatureSensorRefList.at(i).toElement()};
            QString temperatureSensorName{temperatureSensorRefElem.attribute(nameAttr())};
            QString temperatureSensorPropertyName{temperatureSensorRefElem.attribute(propertyAttr())};

            ret = hook().temperatureSensorRefDeclaration(temperatureSensorName,temperatureSensorPropertyName);
        }
    }

    hook().temperatureSensorsDeclarationEnd();

    return ret;
}

bool HeatingManagerConfDocument::extractScheduler(QDomElement &controlElem,
                                                  const QString& observableName)
{
    bool ret{true};
    QDomNodeList descendants{controlElem.elementsByTagName(plugframe::core::scheduler::SchedulerElement::schedulerTag())};
    QString schedulerId{observableName + "_scheduler"};

    if (descendants.size() == 1) // Only one optional scheduler is expected
    {
        QDomElement elem{descendants.at(0).toElement()};
        plugframe::core::scheduler::SchedulerElementHook& schedulHook{hook().schedulerDeclarationBegin()};
        plugframe::core::scheduler::SchedulerElement schedulElem{elem,schedulHook};

        schedulElem.browse(schedulerId);

        hook().schedulerDeclarationEnd();
    }

    return ret;
}


