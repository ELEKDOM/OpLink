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


#ifndef VIRTUALEQUIPMENTSETFACTORY_H
#define VIRTUALEQUIPMENTSETFACTORY_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "olcore-lib_forward.h"
#include "factory/bundlefactory.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipmentset
{
namespace factory
{

class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetFactory : public plugframe::core::bundle::BundleFactory
{
public:
    VirtualEquipmentSetFactory();
    ~VirtualEquipmentSetFactory() override;

public:
    virtual VirtualEquipmentSetLoader* createVirtualEquipmentSetLoader(virtualequipment::VirtualEquipmentLoader *veLoader);
    virtual virtualequipment::VirtualEquipmentLoader* createVirtualEquipmentLoader(bundle::VirtualEquipmentSet *veSet) = 0;
    virtual virtualequipment::VirtualEquipmentConfDocument *createVirtualEquipmentConfDocument(virtualequipment::VirtualEquipmentLoaderHook& hook) = 0;

protected:
    virtual service::VirtualEquipmentSetService *createVirtualEquipmentSetService(plugframe::core::bundle::BundleImplementation *implementation);
    plugframe::core::bundle::BundleBuilder *createBuilder(plugframe::core::bundle::Bundle& myBundle) override;
    plugframe::core::service::ServiceImplementationInterface *createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation,
                                                                                          const QString& sName,
                                                                                          const QString& serviceVersion) override;
};

}//namespace factory
}//namespace virtualequipmentset
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTSETFACTORY_H
