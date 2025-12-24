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

ServerEngineFactory::ServerEngineFactory()

{

}

ServerEngineFactory::~ServerEngineFactory()
{

}

plugframe::ServiceImplementationInterface *ServerEngineFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                            const QString &sName,
                                                                                            const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (oplink::ObservableServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createObservableService(implementation);
        }
    }

    return ret;
}

plugframe::BundleListener *ServerEngineFactory::createBundleListener(plugframe::Bundle &myBundle)
{
    return new ServerEngineListener{myBundle};
}

ObservableService *ServerEngineFactory::createObservableService(plugframe::BundleImplementation *implementation)
{
    return new ObservableService{implementation};
}
