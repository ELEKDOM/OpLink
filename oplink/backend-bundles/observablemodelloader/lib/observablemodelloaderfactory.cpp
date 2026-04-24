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

#include "observablemodelloaderfactory.h"
#include "observablemodelloaderemitter.h"
#include "observablemodelloaderlistener.h"
#include "observable/property/propertyclassnames.h"
#include "observable/processor/processorclassnames.h"
#include "observable/observable/observableclassnames.h"
#include "model/property/loadpropertymodel.h"
#include "model/property/actuatorpropertymodel.h"
#include "model/property/sensorpropertymodel.h"
#include "model/processor/lowprocessor/loadcommandprocessormodel.h"
#include "model/processor/lowprocessor/expectedvaluecheckcommandprocessormodel.h"
#include "model/processor/lowprocessor/expectedvaluenocheckcommandprocessormodel.h"
#include "model/observable/lowobservable/loadmodel.h"
#include "model/observable/lowobservable/actuatormodel.h"
#include "model/observable/lowobservable/sensormodel.h"
#include "event/specificpropertiesmodelloadingevent.h"
#include "event/processorsmodelloadingevent.h"
#include "event/observablemodelsloadingevent.h"

ObservableModelLoaderFactory::ObservableModelLoaderFactory()
{

}

ObservableModelLoaderFactory::~ObservableModelLoaderFactory()
{

}

PF_createServiceImplementation_DEF(ObservableModelLoaderFactory)

plugframe::BundleEmitter *ObservableModelLoaderFactory::createBundleEmitter(plugframe::Bundle &myBundle)
{
    return new ObservableModelLoaderEmitter{myBundle};
}

plugframe::BundleListener *ObservableModelLoaderFactory::createBundleListener(plugframe::Bundle &myBundle)
{
    return new ObservableModelLoaderListener{myBundle};
}

SpecificPropertiesModelLoadingEvent *ObservableModelLoaderFactory::createSpecificPropertiesModelLoadingEvent(unsigned short cpt)
{
    return new SpecificPropertiesModelLoadingEvent{cpt};
}

ProcessorsModelLoadingEvent *ObservableModelLoaderFactory::createProcessorsModelLoadingEvent(unsigned short cpt)
{
    return new ProcessorsModelLoadingEvent{cpt};
}

ObservableModelsLoadingEvent *ObservableModelLoaderFactory::createObservableModelsLoadingEvent(unsigned short cpt)
{
    return new ObservableModelsLoadingEvent{cpt};
}

oplink::ObservablePropertyModel *ObservableModelLoaderFactory::createObservablePropertyModel(const oplink::PropertyModelName& modelName,
                                                                                             const oplink::PropertyName &propertyId,
                                                                                             const oplink::PropertyType &propertyType)
{
    oplink::ObservablePropertyModel *ret{nullptr};

    if(oplink::PropertyClassNames::PROPERTY_CLASS == propertyType)
    {
        ret = createPropertyModel(modelName, propertyId);
    }
    else if(oplink::PropertyClassNames::LOAD_PROPERTY_CLASS == propertyType)
    {
        ret = createLoadPropertyModel(modelName, propertyId);
    }
    else if(oplink::PropertyClassNames::ACTUATOR_PROPERTY_CLASS == propertyType)
    {
        ret = createActuatorPropertyModel(modelName, propertyId);
    }
    else if(oplink::PropertyClassNames::SENSOR_PROPERTY_CLASS == propertyType)
    {
        ret = createSensorPropertyModel(modelName, propertyId);
    }

    return ret;
}

oplink::ObservablePropertyModel *ObservableModelLoaderFactory::createPropertyModel(const oplink::PropertyModelName &modelName,
                                                                                   const oplink::PropertyName &propertyId)
{
    return new oplink::ObservablePropertyModel{modelName, propertyId};
}

oplink::ObservablePropertyModel *ObservableModelLoaderFactory::createLoadPropertyModel(const oplink::PropertyModelName &modelName,
                                                                                       const oplink::PropertyName &propertyId)
{
    return new oplink::LoadPropertyModel{modelName, propertyId};
}

oplink::ObservablePropertyModel *ObservableModelLoaderFactory::createActuatorPropertyModel(const oplink::PropertyModelName &modelName,
                                                                                           const oplink::PropertyName &propertyId)
{
    return new oplink::ActuatorPropertyModel{modelName, propertyId};
}

oplink::ObservablePropertyModel *ObservableModelLoaderFactory::createSensorPropertyModel(const oplink::PropertyModelName &modelName,
                                                                                         const oplink::PropertyName &propertyId)
{
    return new oplink::SensorPropertyModel{modelName, propertyId};
}

oplink::CommandProcessorModel *ObservableModelLoaderFactory::createCommandProcessorModel(const oplink::ProcessorModelName& modelName,
                                                                                         const oplink::CommandName& commandName,
                                                                                         const oplink::ProcessorType& proccessorType)
{
    oplink::CommandProcessorModel  *ret{nullptr};

    if(oplink::ProcessorClassNames::LOAD_COMMAND_PROCESSOR_CLASS == proccessorType)
    {
        ret = createLoadCommandProcessorModel(modelName, commandName);
    }
    else if(oplink::ProcessorClassNames::EXPECTED_VALUE_CHECK_COMMAND_PROCESSOR_CLASS == proccessorType)
    {
        ret = createCheckCommandProcessorModel(modelName, commandName);
    }
    else if(oplink::ProcessorClassNames::EXPECTED_VALUE_NO_CHECK_COMMAND_PROCESSOR_CLASS == proccessorType)
    {
        ret = createNoCheckCommandProcessorModel(modelName, commandName);
    }

    return ret;
}

oplink::CommandProcessorModel *ObservableModelLoaderFactory::createLoadCommandProcessorModel(const oplink::ProcessorModelName &modelName,
                                                                                             const oplink::CommandName &commandName)
{
    return new oplink::LoadCommandProcessorModel{modelName, commandName};
}

oplink::CommandProcessorModel *ObservableModelLoaderFactory::createCheckCommandProcessorModel(const oplink::ProcessorModelName &modelName,
                                                                                              const oplink::CommandName &commandName)
{
    return new oplink::ExpectedValueCheckCommandProcessorModel{modelName, commandName};
}

oplink::CommandProcessorModel *ObservableModelLoaderFactory::createNoCheckCommandProcessorModel(const oplink::ProcessorModelName &modelName,
                                                                                                const oplink::CommandName &commandName)
{
    return new oplink::ExpectedValueNoCheckCommandProcessorModel{modelName, commandName};
}

oplink::ObservableModel *ObservableModelLoaderFactory::createObservableModel(const oplink::ObservableModelName &name,
                                                                             const oplink::ObservableType &className)
{
    oplink::ObservableModel  *ret{nullptr};

    if (oplink::ObservableClassNames::LOAD_CLASS == className)
    {
        ret = createLoadObservableModel(name);
    }
    else if (oplink::ObservableClassNames::ACTUATOR_CLASS == className)
    {
        ret = createActuatorObservableModel(name);
    }
    else if (oplink::ObservableClassNames::SENSOR_CLASS == className)
    {
        ret = createSensorObservableModel(name);
    }

    return ret;
}

oplink::ObservableModel *ObservableModelLoaderFactory::createLoadObservableModel(const oplink::ObservableModelName &modelName)
{
    return new oplink::LoadModel{modelName};
}

oplink::ObservableModel *ObservableModelLoaderFactory::createActuatorObservableModel(const oplink::ObservableModelName &modelName)
{
    return new oplink::ActuatorModel{modelName};
}

oplink::ObservableModel *ObservableModelLoaderFactory::createSensorObservableModel(const oplink::ObservableModelName &modelName)
{
    return new oplink::SensorModel{modelName};
}
