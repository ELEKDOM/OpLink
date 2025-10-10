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


#include "observablemodelregisterplugin.h"
#include "observablemodelregister.h"
#include "observablebuilderservice.h"
#include "modelregisterservice.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablemodel.h"
#include "model/observable/observablebuilderargs.h"
#include "observable/observable/observablebuilder.h"

using namespace elekdom::oplink::observablemodelregister::plugin;

ObservableModelRegisterPlugin::ObservableModelRegisterPlugin()
{

}

ObservableModelRegisterPlugin::~ObservableModelRegisterPlugin()
{

}

bundle::Bundle4PluginInterface *ObservableModelRegisterPlugin::createImplementation()
{
    return new observablemodelregister::bundle::ObservableModelRegister;
}

void ObservableModelRegisterPlugin::bindServicesImplementations()
{
    plugframe::core::service::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(ModelRegisterServiceInterface::serviceName());
    m_modelRegisterServiceImpl = serviceImplementationItf.dynamicCast<service::ModelRegisterService>();

    serviceImplementationItf = implementation()->getServiceImplementation(ObservableBuilderServiceInterface::serviceName());
    m_observableBuilderServiceImpl = serviceImplementationItf.dynamicCast<service::ObservableBuilderService>();
}

bool ObservableModelRegisterPlugin::addPropertyModel(core::model::QspObservablePropertyModel model)
{
    return m_modelRegisterServiceImpl->addPropertyModel(model);
}

elekdom::oplink::core::model::QspObservablePropertyModel ObservableModelRegisterPlugin::getPropertyModel(core::model::PropertyModelName id)
{
    return m_modelRegisterServiceImpl->getPropertyModel(id);
}

bool ObservableModelRegisterPlugin::addProcessorModel(core::model::QspCommandProcessorModel model)
{
    return m_modelRegisterServiceImpl->addProcessorModel(model);
}

elekdom::oplink::core::model::QspCommandProcessorModel ObservableModelRegisterPlugin::getProcessorModel(core::model::ProcessorModelName id)
{
    return m_modelRegisterServiceImpl->getProcessorModel(id);
}

bool ObservableModelRegisterPlugin::addObservableModel(core::model::QspObservableModel model)
{
    return m_modelRegisterServiceImpl->addObservableModel(model);
}

elekdom::oplink::core::observable::QspObservableBuilder ObservableModelRegisterPlugin::buildObservable(core::model::QspObservableBuilderArgs builderargs)
{
    return m_observableBuilderServiceImpl->buildObservable(builderargs);
}
