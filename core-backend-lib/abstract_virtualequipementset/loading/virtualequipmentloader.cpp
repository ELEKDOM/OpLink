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

using namespace elekdom::oplink::core;
using namespace elekdom::oplink::core::virtualequipment;

VirtualEquipmentLoader::VirtualEquipmentLoader(virtualequipmentset::bundle::VirtualEquipmentSet *veSet) :
    m_veSet{veSet}
{
}

VirtualEquipmentLoader::~VirtualEquipmentLoader()
{

}

void VirtualEquipmentLoader::confDocument(virtualequipment::VirtualEquipmentConfDocument *confDoc)
{
    m_confDoc.reset(confDoc);
}

void VirtualEquipmentLoader::load(QString fileName)
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

observable::QspObservable VirtualEquipmentLoader::newly()
{
    return m_newlyVirtualEquipment;
}

void VirtualEquipmentLoader::newly(observable::Observable *newve)
{
    m_newlyVirtualEquipment.reset(newve);
}

bool VirtualEquipmentLoader::buildMandatoryProperties(const QString& observableName,
                                                      const QString& modelName,
                                                      const QString& localisation,
                                                      int confId)
{
    bool ret{true};
    observable::Property *prop;
    observable::ObservableBuilder *obsBuilder{dynamic_cast<observable::ObservableBuilder*>(m_newlyVirtualEquipment.data())};

    // Name
    //-----
    prop = new observable::Property{*m_newlyVirtualEquipment,
                                    observable::PropertyId::P_NAME,
                                    QMetaType::QString};
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(observable::PropertyId::P_NAME,observableName);

    // Model Name
    //-----------
    prop = new observable::Property{*m_newlyVirtualEquipment,
                                    observable::PropertyId::P_MODEL,
                                    QMetaType::QString};
    prop->value(modelName);
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(observable::PropertyId::P_MODEL,modelName);


    // Localisation
    //-------------
    prop = new observable::Property{*m_newlyVirtualEquipment,
                                    observable::PropertyId::P_LOCALISATION,
                                    QMetaType::QString};
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(observable::PropertyId::P_LOCALISATION,localisation);

    // Conf Id
    //--------
    prop = new observable::Property{*m_newlyVirtualEquipment,
                                    observable::PropertyId::P_CONF,
                                    QMetaType::Int};
    obsBuilder->addProperty(prop);
    obsBuilder->setMandatoryPropertyValue(observable::PropertyId::P_CONF,confId);

    // Mode (assigned later)
    //----------------------
    prop = new observable::Property{*m_newlyVirtualEquipment,
                                    observable::PropertyId::P_MODE,
                                    QMetaType::QString};
    obsBuilder->addProperty(prop);

    return ret;
}

void VirtualEquipmentLoader::modeValue(const QString &val)
{
    observable::QspProperty property{m_newlyVirtualEquipment->property(observable::PropertyId::P_MODE)};

    property->value(val);
}


void VirtualEquipmentLoader::addProperty(const observable::PropertyName &propertyName,
                                         QMetaType::Type valueType)
{
    observable::Property *prop;
    observable::ObservableBuilder *obsBuilder{dynamic_cast<observable::ObservableBuilder*>(m_newlyVirtualEquipment.data())};

    prop = new observable::Property{*m_newlyVirtualEquipment,
                                    propertyName,
                                    valueType};
    obsBuilder->addProperty(prop);
}

void VirtualEquipmentLoader::addGroupProperty(const QString &groupName,
                                              const observable::PropertyName &propertyName,
                                              QMetaType::Type valueType)
{
    addProperty(observable::PropertyId::groupPropertyName(groupName, propertyName),
                valueType);
}



observable::monitoring::StateToWatch *VirtualEquipmentLoader::createStateToWatch(const observable::ObservableName &observableName,
                                                                                 const observable::PropertyName &propertyName)
{
    observable::monitoring::StateToWatch *ret{nullptr};
    engine::service::ObservableServiceInterface* os;

    os = veSet()->observableService();
    if (os)
    {
        core::observable::QspProperty property;

        property = os->property(observableName,propertyName);
        if (!property.isNull())
        {
            ret = new observable::monitoring::StateToWatch(property);
        }
    }

    return ret;
}
