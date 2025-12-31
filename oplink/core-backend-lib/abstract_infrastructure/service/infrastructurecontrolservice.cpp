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

#include "infrastructurecontrolservice.h"
#include "abstract_infrastructure/infrastructure.h"

oplink::InfrastructureControlService::InfrastructureControlService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

oplink::InfrastructureControlService::~InfrastructureControlService()
{

}

const QString& oplink::InfrastructureControlService::getInfrastructureName()
{
    oplink::Infrastructure* infra{dynamic_cast<oplink::Infrastructure*>(implementation())};
    return infra->getInfrastructureName();
}

bool oplink::InfrastructureControlService::startLoadingInfrastructure(plugframe::WorkerWatcher *workerWatcher,
                                                                      oplink::InfrastructureControlServiceInterface::OperationalMode mode)
{
    oplink::Infrastructure* infra{dynamic_cast<oplink::Infrastructure*>(implementation())};
    return infra->startLoadingInfrastructure(mode, workerWatcher);
}

bool oplink::InfrastructureControlService::loadingFinished()
{
    oplink::Infrastructure* infra{dynamic_cast<oplink::Infrastructure*>(implementation())};
    return infra->loadingFinished();
}

QString oplink::InfrastructureControlService::serviceName()
{
    return InfrastructureControlServiceInterface::serviceName();
}

