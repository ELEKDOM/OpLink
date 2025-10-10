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


#include "bundle/bundle.h"
#include "observablemodelregisterfactory.h"
#include "observablemodelregister.h"
#include "service-int/modelregisterserviceinterface.h"
#include "service-int/observablebuilderserviceinterface.h"

using namespace elekdom::oplink::observablemodelregister::factory;
using namespace elekdom::oplink::observablemodelregister::service;
using namespace elekdom::oplink::observablemodelregister::bundle;

ObservableModelRegisterFactory::ObservableModelRegisterFactory()
{

}

ObservableModelRegisterFactory::~ObservableModelRegisterFactory()
{

}

ModelRegisterService *ObservableModelRegisterFactory::createModelRegisterService(elekdom::plugframe::core::bundle::BundleImplementation *implementation)
{
    return new ModelRegisterService{implementation};
}

ObservableBuilderService *ObservableModelRegisterFactory::createObservableBuilderService(elekdom::plugframe::core::bundle::BundleImplementation *implementation)
{
    return new ObservableBuilderService{implementation};
}

elekdom::plugframe::core::service::ServiceImplementationInterface *ObservableModelRegisterFactory::createServiceImplementation(elekdom::plugframe::core::bundle::BundleImplementation *implementation,
                                                                                                     const QString &sName,
                                                                                                     const QString &serviceVersion)
{
    plugframe::core::service::ServiceImplementationInterface *ret{nullptr};

    if (service::ModelRegisterServiceInterface::serviceName() == sName)
    {
        if (plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createModelRegisterService(implementation);
        }
    }
    else if (service::ObservableBuilderServiceInterface::serviceName() == sName)
    {
        if (plugin::ServiceInterface::V_100() == serviceVersion)
        {
            ret = createObservableBuilderService(implementation);
        }
    }

    return ret;
}


