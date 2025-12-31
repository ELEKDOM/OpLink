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

#include "virtualequipmentsetservice.h"
#include "abstract_virtualequipementset/virtualequipmentset.h"
#include "service-int/virtualequipmentsetserviceinterface.h"

oplink::VirtualEquipmentSetService::VirtualEquipmentSetService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

oplink::VirtualEquipmentSetService::~VirtualEquipmentSetService()
{

}

const QString& oplink::VirtualEquipmentSetService::getVirtualEquipmentSetName()
{
    oplink::VirtualEquipmentSet* veSet{dynamic_cast<oplink::VirtualEquipmentSet*>(implementation())};

    return veSet->getVirtualEquipmentSetName();
}

bool oplink::VirtualEquipmentSetService::startLoading(plugframe::WorkerWatcher *workerWatcher)
{
    oplink::VirtualEquipmentSet* veSet{dynamic_cast<oplink::VirtualEquipmentSet*>(implementation())};

    return veSet->startLoading(workerWatcher);
}

bool oplink::VirtualEquipmentSetService::loadingFinished()
{
    oplink::VirtualEquipmentSet* veSet{dynamic_cast<oplink::VirtualEquipmentSet*>(implementation())};

    return veSet->isLoadingFinished();
}

QString oplink::VirtualEquipmentSetService::serviceName()
{
    return VirtualEquipmentSetServiceInterface::serviceName();
}
