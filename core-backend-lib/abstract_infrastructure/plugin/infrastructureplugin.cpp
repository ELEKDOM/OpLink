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

#include "infrastructureplugin.h"
#include "service/serviceimplementationinterface.h"
#include "bundle/bundle4plugininterface.h"
#include "abstract_infrastructure/service/infrastructurecontrolservice.h"

oplink::InfrastructurePlugin::InfrastructurePlugin()
{

}

oplink::InfrastructurePlugin::~InfrastructurePlugin()
{

}

void oplink::InfrastructurePlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(oplink::InfrastructureControlServiceInterface::serviceName());
    m_controlServiceImpl = serviceImplementationItf.dynamicCast<oplink::InfrastructureControlService>();
}

const oplink::InfrastructureName &oplink::InfrastructurePlugin::getInfrastructureName()
{
    return m_controlServiceImpl->getInfrastructureName();
}

bool oplink::InfrastructurePlugin::startLoadingInfrastructure(plugframe::WorkerWatcher *workerWatcher,
                                                              oplink::InfrastructureControlServiceInterface::OperationalMode mode)
{
    return m_controlServiceImpl->startLoadingInfrastructure(workerWatcher, mode);
}

bool oplink::InfrastructurePlugin::loadingFinished()
{
    return m_controlServiceImpl->loadingFinished();
}
