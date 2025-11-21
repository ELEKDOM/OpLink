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

#include "virtualequipmentsetplugin.h"
#include "bundle/bundle4plugininterface.h"
#include "abstract_virtualequipementset/service/virtualequipmentsetservice.h"

oplink::VirtualEquipmentSetPlugin::VirtualEquipmentSetPlugin()
{

}

oplink::VirtualEquipmentSetPlugin::~VirtualEquipmentSetPlugin()
{

}

void oplink::VirtualEquipmentSetPlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(oplink::VirtualEquipmentSetServiceInterface::serviceName());
    m_virtualEquipmentSetServiceImpl = serviceImplementationItf.dynamicCast<oplink::VirtualEquipmentSetService>();
}

const QString& oplink::VirtualEquipmentSetPlugin::getVirtualEquipmentSetName()
{
    return m_virtualEquipmentSetServiceImpl->getVirtualEquipmentSetName();
}

bool oplink::VirtualEquipmentSetPlugin::startLoading(plugframe::WorkerWatcher *workerWatcher)
{
    return m_virtualEquipmentSetServiceImpl->startLoading(workerWatcher);
}

bool oplink::VirtualEquipmentSetPlugin::loadingFinished()
{
    return m_virtualEquipmentSetServiceImpl->loadingFinished();
}
