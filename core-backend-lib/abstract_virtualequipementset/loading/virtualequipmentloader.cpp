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

#include "virtualequipmentloader.h"
#include "abstract_virtualequipementset/virtualequipmentset.h"
#include "observable/virtualequipment/virtualequipmentconfdocument.h"
#include "observable/property/property.h"
#include "observable/property/propertyid.h"
#include "observable/observable/observable.h"
#include "observable/highobservable/monitor/statetowatch.h"

oplink::VirtualEquipmentLoader::VirtualEquipmentLoader(oplink::VirtualEquipmentSet *veSet) :
    m_veSet{veSet}
{
}

oplink::VirtualEquipmentLoader::~VirtualEquipmentLoader()
{

}

void oplink::VirtualEquipmentLoader::confDocument(oplink::VirtualEquipmentConfDocument *confDoc)
{
    m_confDoc.reset(confDoc);
}

void oplink::VirtualEquipmentLoader::load(QString fileName)
{
    m_newlyVirtualEquipment.reset();
    m_confDoc->load(fileName);

    if (m_confDoc->fileLoaded())
    {
        if (!m_confDoc->browse())
        {
            m_newlyVirtualEquipment.reset();
        }
    }
}

oplink::QspObservable oplink::VirtualEquipmentLoader::newly()
{
    return m_newlyVirtualEquipment;
}

void oplink::VirtualEquipmentLoader::newly(oplink::Observable *newve)
{
    m_newlyVirtualEquipment.reset(newve);
}

bool oplink::VirtualEquipmentLoader::buildMandatoryProperties(const QString& observableName,
                                                              const QString& modelName,
                                                              const QString& localisation,
                                                              int confId)
{
    bool ret{true};
    oplink::Property *prop;
    oplink::ObservableBuilder *obsBuilder{dynamic_cast<oplink::ObservableBuilder*>(m_newlyVirtualEquipment.data())};

    // Name
    //-----
    prop = new oplink::Property{*m_newlyVirtualEquipment,
                                oplink::PropertyId::P_NAME,
                                QMetaType::QString};
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_NAME,observableName);

    // Model Name
    //-----------
    prop = new oplink::Property{*m_newlyVirtualEquipment,
                                oplink::PropertyId::P_MODEL,
                                QMetaType::QString};
    prop->value(modelName);
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_MODEL,modelName);

    // Localisation
    //-------------
    prop = new oplink::Property{*m_newlyVirtualEquipment,
                                oplink::PropertyId::P_LOCALISATION,
                                QMetaType::QString};
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_LOCALISATION,localisation);

    // Conf Id
    //--------
    prop = new oplink::Property{*m_newlyVirtualEquipment,
                                oplink::PropertyId::P_CONF,
                                QMetaType::Int};
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_CONF,confId);

    // Mode (assigned later)
    //----------------------
    prop = new oplink::Property{*m_newlyVirtualEquipment,
                                oplink::PropertyId::P_MODE,
                                QMetaType::QString};
    obsBuilder->addProperty(prop);

    return ret;
}

void oplink::VirtualEquipmentLoader::modeValue(const QString &val)
{
    oplink::QspProperty property{m_newlyVirtualEquipment->property(oplink::PropertyId::P_MODE)};

    property->value(val);
}


void oplink::VirtualEquipmentLoader::addProperty(const oplink::PropertyName &propertyName,
                                                 QMetaType::Type valueType)
{
    oplink::Property *prop;
    oplink::ObservableBuilder *obsBuilder{dynamic_cast<oplink::ObservableBuilder*>(m_newlyVirtualEquipment.data())};

    prop = new oplink::Property{*m_newlyVirtualEquipment,
                                propertyName,
                                valueType};
    obsBuilder->addProperty(prop);
}

void oplink::VirtualEquipmentLoader::addGroupProperty(const QString &groupName,
                                                      const oplink::PropertyName &propertyName,
                                                      QMetaType::Type valueType)
{
    addProperty(oplink::PropertyId::groupPropertyName(groupName, propertyName),
                valueType);
}



oplink::StateToWatch *oplink::VirtualEquipmentLoader::createStateToWatch(const oplink::ObservableName &observableName,
                                                                         const oplink::PropertyName &propertyName)
{
    oplink::StateToWatch *ret{nullptr};
    oplink::ObservableServiceInterface* os;

    os = veSet()->observableService();
    if (os)
    {
        oplink::QspProperty property;

        property = os->property(observableName,propertyName);
        if (!property.isNull())
        {
            ret = new oplink::StateToWatch(property);
        }
    }

    return ret;
}
