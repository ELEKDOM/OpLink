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


#include "virtualequipmentsetfactory.h"
#include "virtualequipmentsetbuilder.h"
#include "virtualequipmentset.h"
#include "service/virtualequipmentsetservice.h"
#include "service-int/virtualequipmentsetserviceinterface.h"
#include "loading/virtualequipmentsetloader.h"
#include "loading/virtualequipmentloader.h"
#include "bundle/bundle.h"

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::oplink::core::virtualequipmentset;
using namespace elekdom::oplink::core::virtualequipmentset::factory;
using namespace elekdom::oplink::core::virtualequipmentset::service;

VirtualEquipmentSetFactory::VirtualEquipmentSetFactory()
{

}

VirtualEquipmentSetFactory::~VirtualEquipmentSetFactory()
{

}

VirtualEquipmentSetService *VirtualEquipmentSetFactory::createVirtualEquipmentSetService(plugframe::core::bundle::BundleImplementation *implementation)
{
    return new VirtualEquipmentSetService{implementation};
}

VirtualEquipmentSetLoader *VirtualEquipmentSetFactory::createVirtualEquipmentSetLoader(virtualequipment::VirtualEquipmentLoader *veLoader)
{
    return new VirtualEquipmentSetLoader{veLoader};
}

BundleBuilder *VirtualEquipmentSetFactory::createBuilder(plugframe::core::bundle::Bundle &myBundle)
{
    return new virtualequipmentset::builder::VirtualEquipmentSetBuilder{myBundle};
}

elekdom::plugframe::core::service::ServiceImplementationInterface *VirtualEquipmentSetFactory::createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation,
                                                                                                                           const QString &sName,
                                                                                                                           const QString &serviceVersion)
{
    elekdom::plugframe::core::service::ServiceImplementationInterface *ret{nullptr};
    Q_UNUSED(serviceVersion) // not implemented in this release !

    if (service::VirtualEquipmentSetServiceInterface::serviceName() == sName)
    {
        ret = createVirtualEquipmentSetService(implementation);
    }

    return ret;
}
