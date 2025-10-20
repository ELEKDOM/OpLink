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


#ifndef VIRTUALEQUIPMENTLOADER_H
#define VIRTUALEQUIPMENTLOADER_H

#include <QVariant>
#include "olcore-backend-lib_forward.h"
#include "olcore-lib_forward.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipment
{

class VirtualEquipmentLoader
{
public:
    VirtualEquipmentLoader(virtualequipmentset::bundle::VirtualEquipmentSet *veSet);
    virtual ~VirtualEquipmentLoader();

public:
    virtual virtualequipment::VirtualEquipmentLoaderHook& loaderHook() = 0;
    void load(QString fileName);
    void confDocument(virtualequipment::VirtualEquipmentConfDocument *confDoc);
    virtualequipmentset::bundle::VirtualEquipmentSet *veSet() {return m_veSet;}
    observable::QspObservable newly();

protected:
    void newly(observable::Observable *newve);
    bool buildMandatoryProperties(const QString& observableName,
                                  const QString& modelName,
                                  const QString& localisation,
                                  int confId);
    void modeValue(const QString& val);





    virtual observable::monitoring::StateToWatch *createStateToWatch(const observable::ObservableName& observableName,
                                                                     const observable::PropertyName& propertyName);

    void addProperty(const observable::PropertyName& propertyName, QMetaType::Type valueType);
    void addGroupProperty(const QString& groupName,
                          const observable::PropertyName& propertyName,
                          QMetaType::Type valueType);


private:
    virtualequipmentset::bundle::VirtualEquipmentSet *m_veSet;
    virtualequipment::QspVirtualEquipmentConfDocument m_confDoc;
    observable::QspObservable                         m_newlyVirtualEquipment;
};

}//namespace virtualequipment
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTLOADER_H
