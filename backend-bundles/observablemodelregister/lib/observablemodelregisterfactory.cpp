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

#include "observablemodelregisterfactory.h"
#include "modelregisterservice.h"
#include "observablebuilderservice.h"
#include "service-int/modelregisterserviceinterface.h"
#include "service-int/observablebuilderserviceinterface.h"

ObservableModelRegisterFactory::ObservableModelRegisterFactory()
{

}

ObservableModelRegisterFactory::~ObservableModelRegisterFactory()
{

}

ModelRegisterService *ObservableModelRegisterFactory::createModelRegisterService(plugframe::BundleImplementation *implementation)
{
    return new ModelRegisterService{implementation};
}

ObservableBuilderService *ObservableModelRegisterFactory::createObservableBuilderService(plugframe::BundleImplementation *implementation)
{
    return new ObservableBuilderService{implementation};
}

plugframe::ServiceImplementationInterface *ObservableModelRegisterFactory::createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                                       const QString &sName,
                                                                                                       const QString &serviceVersion)
{
    plugframe::ServiceImplementationInterface *ret{nullptr};

    if (oplink::ModelRegisterServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createModelRegisterService(implementation);
        }
    }
    else if (oplink::ObservableBuilderServiceInterface::serviceName() == sName)
    {
        if (plugframe::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createObservableBuilderService(implementation);
        }
    }

    return ret;
}


