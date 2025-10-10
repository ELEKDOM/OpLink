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


using namespace elekdom::oplink::core::infrastructure::plugin;

InfrastructurePlugin::InfrastructurePlugin()
{

}

InfrastructurePlugin::~InfrastructurePlugin()
{

}

void InfrastructurePlugin::bindServicesImplementations()
{
    plugframe::core::service::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(InfrastructureControlServiceInterface::serviceName());
    m_controlServiceImpl = serviceImplementationItf.dynamicCast<service::InfrastructureControlService>();
}

const elekdom::oplink::core::infrastructure::InfrastructureName &InfrastructurePlugin::getInfrastructureName()
{
    return m_controlServiceImpl->getInfrastructureName();
}

bool InfrastructurePlugin::startLoadingInfrastructure(elekdom::plugframe::core::worker::WorkerWatcher *workerWatcher, elekdom::oplink::core::infrastructure::service::InfrastructureControlServiceInterface::OperationalMode mode)
{
    return m_controlServiceImpl->startLoadingInfrastructure(workerWatcher, mode);
}

bool InfrastructurePlugin::loadingFinished()
{
    return m_controlServiceImpl->loadingFinished();
}
