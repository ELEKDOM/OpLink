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


#include "modelregisterservice.h"
#include "observablemodelregister.h"
#include "service-int/modelregisterserviceinterface.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablemodel.h"

using namespace elekdom::oplink::observablemodelregister::service;
using namespace elekdom::oplink::core;


ModelRegisterService::ModelRegisterService(plugframe::core::bundle::BundleImplementation *implementation):
    ObservableModelRegisterServiceImplementation{implementation}
{

}

ModelRegisterService::~ModelRegisterService()
{

}

bool ModelRegisterService::addPropertyModel(model::QspObservablePropertyModel model)
{
    return observableModelRegister()->addPropertyModel(model);
}

model::QspObservablePropertyModel ModelRegisterService::getPropertyModel(model::PropertyModelName id)
{
    return observableModelRegister()->getPropertyModel(id);
}

bool ModelRegisterService::addProcessorModel(model::QspCommandProcessorModel model)
{
    return observableModelRegister()->addProcessorModel(model);
}

model::QspCommandProcessorModel ModelRegisterService::getProcessorModel(model::ProcessorModelName id)
{
    return observableModelRegister()->getProcessorModel(id);
}

bool ModelRegisterService::addObservableModel(model::QspObservableModel model)
{
    return observableModelRegister()->addObservableModel(model);
}

QString ModelRegisterService::serviceName()
{
    return service::ModelRegisterServiceInterface::serviceName();
}
