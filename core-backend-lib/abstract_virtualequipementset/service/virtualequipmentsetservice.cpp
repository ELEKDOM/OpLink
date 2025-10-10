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

using namespace elekdom::oplink::core::virtualequipmentset::service;
using namespace elekdom::oplink::core::virtualequipmentset;

VirtualEquipmentSetService::VirtualEquipmentSetService(plugframe::core::bundle::BundleImplementation *implementation):
plugframe::core::service::ServiceImplementation{implementation}
{

}

VirtualEquipmentSetService::~VirtualEquipmentSetService()
{

}

const QString &VirtualEquipmentSetService::getVirtualEquipmentSetName()
{
    bundle::VirtualEquipmentSet* veSet{dynamic_cast<bundle::VirtualEquipmentSet*>(implementation())};

    return veSet->getVirtualEquipmentSetName();
}

bool VirtualEquipmentSetService::startLoading(plugframe::core::worker::WorkerWatcher *workerWatcher)
{
    bundle::VirtualEquipmentSet* veSet{dynamic_cast<bundle::VirtualEquipmentSet*>(implementation())};

    return veSet->startLoading(workerWatcher);
}

bool VirtualEquipmentSetService::loadingFinished()
{
    bundle::VirtualEquipmentSet* veSet{dynamic_cast<bundle::VirtualEquipmentSet*>(implementation())};

    return veSet->isLoadingFinished();
}

QString VirtualEquipmentSetService::serviceName()
{
    return VirtualEquipmentSetServiceInterface::serviceName();
}
