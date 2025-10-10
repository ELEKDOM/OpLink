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


#include "actuatormodel.h"
#include "model/observable/observablebuilderargs.h"
#include "model/observable/actuatorbuilderargs.h"
#include "observable/observable/observablebuilder.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "observable/property/property.h"
#include "observable/property/operationdeviceproperty.h"
#include "observable/property/loadproperty.h"
#include "abstract_infrastructure/loading/actuatoroutput.h"
#include "abstract_infrastructure/loading/actuatoroutputsbinding.h"

using namespace elekdom::oplink::core::model;
using namespace elekdom::oplink::core;

ActuatorModel::ActuatorModel(const ObservableModelName &name) :
    OperationDeviceModel{name}
{

}

ActuatorModel::~ActuatorModel()
{

}

bool ActuatorModel::checkBuilderArgs(QspObservableBuilderArgs builderArgs)
{
    QspActuatorBuilderArgs actuatorArgs{builderArgs.dynamicCast<ActuatorBuilderArgs>()};
    return !actuatorArgs.isNull();
}

bool ActuatorModel::buildProperties(observable::QspObservableBuilder observableBuilder,
                                      QspObservableBuilderArgs builderArgs)
{
    bool ret{false};
    QspActuatorBuilderArgs actuatorBuilderArgs{builderArgs.dynamicCast<ActuatorBuilderArgs>()};

    if (!actuatorBuilderArgs.isNull())
    {
        ret = OperationDeviceModel::buildProperties(observableBuilder, builderArgs);

        if (ret)
        {
            ret = bindOutputs(observableBuilder,
                              actuatorBuilderArgs->m_actuatorOutputsBinding,
                              actuatorBuilderArgs->m_loadedObservables);
        }
    }
    return ret;
}

bool ActuatorModel::bindOutputs(observable::QspObservableBuilder actuatorBuilder,
                                  const infrastructure::ActuatorOutputsBinding& actuatorOutputsBinding,
                                  const observable::QspObservableBuildersContainer &loadedObservables)
{
    bool ret{true};

    for (int i = 0; i < actuatorOutputsBinding.size() && ret; i++)
    {
        const infrastructure::ActuatorOutput&  binding{actuatorOutputsBinding.at(i)};
        observable::QspProperty                property;
        observable::QspOperationDeviceProperty actuatorProperty;
        observable::QspLoadProperty            loadProperty;
        observable::QspObservableBuilder       loadBuilder;

        property = actuatorBuilder->property(binding.m_actuatorPropertyName);
        actuatorProperty = property.dynamicCast<observable::OperationDeviceProperty>();
        loadedObservables->find(binding.m_loadName, loadBuilder);
        property = loadBuilder->property(binding.m_loadPropertyName);
        loadProperty = property.dynamicCast<observable::LoadProperty>();

        // create links between properties
        ret = !actuatorProperty.isNull() && !loadProperty.isNull();
        if (ret)
        {
            actuatorProperty->slave(loadProperty);
            loadProperty->master(actuatorProperty);
        }
    }
    return ret;
}
