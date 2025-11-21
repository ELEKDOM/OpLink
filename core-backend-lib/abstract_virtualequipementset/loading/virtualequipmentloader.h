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
#include "observable/observable/observable.h"
#include "observable/virtualequipment/virtualequipmentconfdocument.h"
#include "olcore-backend-lib_forward.h"
#include "olcore-lib_forward.h"

namespace oplink
{
class VirtualEquipmentLoader
{
public:
    VirtualEquipmentLoader(VirtualEquipmentSet *veSet);
    virtual ~VirtualEquipmentLoader();

public:
    virtual VirtualEquipmentLoaderHook& loaderHook() = 0;
    void load(QString fileName);
    void confDocument(VirtualEquipmentConfDocument *confDoc);
    VirtualEquipmentSet *veSet() {return m_veSet;}
    QspObservable newly();

protected:
    void newly(Observable *newve);
    bool buildMandatoryProperties(const QString& observableName,
                                  const QString& modelName,
                                  const QString& localisation,
                                  int confId);
    void modeValue(const QString& val);





    virtual StateToWatch *createStateToWatch(const ObservableName& observableName,
                                             const PropertyName& propertyName);

    void addProperty(const PropertyName& propertyName, QMetaType::Type valueType);
    void addGroupProperty(const QString& groupName,
                          const PropertyName& propertyName,
                          QMetaType::Type valueType);


private:
    VirtualEquipmentSet            *m_veSet;
    QspVirtualEquipmentConfDocument m_confDoc;
    QspObservable                   m_newlyVirtualEquipment;
};
using QspVirtualEquipmentLoader = QSharedPointer<VirtualEquipmentLoader>;
}//namespace oplink
#endif // VIRTUALEQUIPMENTLOADER_H
