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


#include "infrastructurefactory.h"
#include "infrastructure.h"
#include "service/infrastructurecontrolservice.h"
#include "service-int/infrastructurecontrolserviceinterface.h"
#include "bundle/bundle.h"

using namespace elekdom::oplink::core::infrastructure::factory;
using namespace elekdom::oplink::core;

InfrastructureFactory::InfrastructureFactory()
{
}

InfrastructureFactory::~InfrastructureFactory()
{

}

infrastructure::service::InfrastructureControlService *infrastructure::factory::InfrastructureFactory::createDeviceInfrastructureControlService(plugframe::core::bundle::BundleImplementation *implementation)
{
    return new infrastructure::service::InfrastructureControlService{implementation};
}

elekdom::plugframe::core::service::ServiceImplementationInterface *InfrastructureFactory::createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation,
                                                                                                                      const QString &sName,
                                                                                                                      const QString &serviceVersion)
{
    elekdom::plugframe::core::service::ServiceImplementationInterface *ret{nullptr};

    if (service::InfrastructureControlServiceInterface::serviceName() == sName)
    {
        if (plugframe::core::plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createDeviceInfrastructureControlService(implementation);
        }
    }

    return ret;
}
