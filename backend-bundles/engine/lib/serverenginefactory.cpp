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


#include "serverenginefactory.h"
#include "serverenginelistener.h"
#include "service-int/observableserviceinterface.h"

using namespace elekdom::plugframe::core;
using namespace elekdom::oplink::engine::factory;

ServerEngineFactory::ServerEngineFactory()

{

}

ServerEngineFactory::~ServerEngineFactory()
{

}

service::ServiceImplementationInterface *ServerEngineFactory::createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation,
                                                                                          const QString &sName,
                                                                                          const QString &serviceVersion)
{
    plugframe::core::service::ServiceImplementationInterface *ret{nullptr};

    if (service::ObservableServiceInterface::serviceName() == sName)
    {
        if (plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createObservableService(implementation);
        }
    }

    return ret;
}

bundle::BundleListener *ServerEngineFactory::createBundleListener(plugframe::core::bundle::Bundle &myBundle)
{
    return new bundle::ServerEngineListener{myBundle};
}

elekdom::oplink::engine::service::ObservableService *ServerEngineFactory::createObservableService(plugframe::core::bundle::BundleImplementation *implementation)
{
    return new engine::service::ObservableService{implementation};
}
