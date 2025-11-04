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
#include "service/virtualequipmentsetservice.h"
#include "service-int/virtualequipmentsetserviceinterface.h"
#include "loading/virtualequipmentsetloader.h"
#include "loading/virtualequipmentloader.h"
#include "bundle/bundle.h"

oplink::VirtualEquipmentSetFactory::VirtualEquipmentSetFactory()
{

}

oplink::VirtualEquipmentSetFactory::~VirtualEquipmentSetFactory()
{

}

oplink::VirtualEquipmentSetService *oplink::VirtualEquipmentSetFactory::createVirtualEquipmentSetService(plugframe::BundleImplementation *implementation)
{
    return new oplink::VirtualEquipmentSetService{implementation};
}

oplink::VirtualEquipmentSetLoader *oplink::VirtualEquipmentSetFactory::createVirtualEquipmentSetLoader(oplink::VirtualEquipmentLoader *veLoader)
{
    return new oplink::VirtualEquipmentSetLoader{veLoader};
}

plugframe::BundleBuilder *oplink::VirtualEquipmentSetFactory::createBuilder(plugframe::Bundle &myBundle)
{
    return new oplink::VirtualEquipmentSetBuilder{myBundle};
}

plugframe::ServiceImplementationInterface *oplink::VirtualEquipmentSetFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                                           const QString &sName,
                                                                                                           const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};
    Q_UNUSED(serviceVersion) // not implemented in this release !

    if (oplink::VirtualEquipmentSetServiceInterface::serviceName() == sName)
    {
        ret = createVirtualEquipmentSetService(implementation);
    }

    return ret;
}
