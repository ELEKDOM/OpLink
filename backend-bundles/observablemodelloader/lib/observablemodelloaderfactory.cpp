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
#include "observablemodelloader.h"
#include "observable/property/propertyclassnames.h"
#include "observable/processor/processorclassnames.h"
#include "observable/observable/observableclassnames.h"
#include "model/property/loadpropertymodel.h"
#include "model/property/actuatorpropertymodel.h"
#include "model/property/sensorpropertymodel.h"
#include "model/processor/loadcommandprocessormodel.h"
#include "model/processor/expectedvaluecheckcommandprocessormodel.h"
#include "model/processor/expectedvaluenocheckcommandprocessormodel.h"
#include "model/observable/loadmodel.h"
#include "model/observable/actuatormodel.h"
#include "model/observable/sensormodel.h"
#include "event/mandatorypropertiesmodelloadingevent.h"
#include "event/specificpropertiesmodelloadingevent.h"
#include "event/processorsmodelloadingevent.h"
#include "event/observablemodelsloadingevent.h"

using namespace elekdom::oplink::observablemodelloader::factory;
using namespace elekdom::oplink::observablemodelloader;
using namespace elekdom::oplink::core;

ObservableModelLoaderFactory::ObservableModelLoaderFactory()
{

}

ObservableModelLoaderFactory::~ObservableModelLoaderFactory()
{

}

PF_createServiceImplementation_DEF(ObservableModelLoaderFactory)

BundleEmitter *ObservableModelLoaderFactory::createBundleEmitter(Bundle &myBundle)
{
    return new bundle::ObservableModelLoaderEmitter{myBundle};
}

BundleListener *ObservableModelLoaderFactory::createBundleListener(Bundle &myBundle)
{
    return new bundle::ObservableModelLoaderListener{myBundle};
}

MandatoryPropertiesModelLoadingEvent *ObservableModelLoaderFactory::createMandatoryPropertiesModelLoadingEvent(unsigned short cpt)
{
    return new MandatoryPropertiesModelLoadingEvent{cpt};
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

model::ObservablePropertyModel *ObservableModelLoaderFactory::createObservablePropertyModel(const model::PropertyModelName& modelName,
                                                                                                  const observable::PropertyName &propertyId,
                                                                                                  const observable::PropertyType &propertyType,
                                                                                                  QVariant::Type valueType)
{
    model::ObservablePropertyModel *ret{nullptr};

    if(observable::PropertyClassNames::PROPERTY_CLASS == propertyType)
    {
        ret = createPropertyModel(modelName, propertyId, valueType);
    }
    else if(observable::PropertyClassNames::LOAD_PROPERTY_CLASS == propertyType)
    {
        ret = createLoadPropertyModel(modelName, propertyId, valueType);
    }
    else if(observable::PropertyClassNames::ACTUATOR_PROPERTY_CLASS == propertyType)
    {
        ret = createActuatorPropertyModel(modelName, propertyId, valueType);
    }
    else if(observable::PropertyClassNames::SENSOR_PROPERTY_CLASS == propertyType)
    {
        ret = createSensorPropertyModel(modelName, propertyId, valueType);
    }

    return ret;
}

model::ObservablePropertyModel *ObservableModelLoaderFactory::createPropertyModel(const model::PropertyModelName &modelName,
                                                                                        const observable::PropertyName &propertyId,
                                                                                        QVariant::Type valueType)
{
    return new model::ObservablePropertyModel{modelName, propertyId, valueType};
}

model::ObservablePropertyModel *ObservableModelLoaderFactory::createLoadPropertyModel(const model::PropertyModelName &modelName,
                                                                                            const observable::PropertyName &propertyId,
                                                                                            QVariant::Type valueType)
{
    return new model::LoadPropertyModel{modelName, propertyId, valueType};
}

model::ObservablePropertyModel *ObservableModelLoaderFactory::createActuatorPropertyModel(const model::PropertyModelName &modelName,
                                                                                                const observable::PropertyName &propertyId,
                                                                                                QVariant::Type valueType)
{
    return new model::ActuatorPropertyModel{modelName, propertyId, valueType};
}

model::ObservablePropertyModel *ObservableModelLoaderFactory::createSensorPropertyModel(const model::PropertyModelName &modelName,
                                                                                              const observable::PropertyName &propertyId,
                                                                                              QVariant::Type valueType)
{
    return new model::SensorPropertyModel{modelName, propertyId, valueType};
}

model::CommandProcessorModel *ObservableModelLoaderFactory::createCommandProcessorModel(const model::ProcessorModelName& modelName,
                                                                                              const command::CommandName& commandName,
                                                                                              const observable::ProcessorType& proccessorType)
{
    model::CommandProcessorModel  *ret{nullptr};

    if(observable::ProcessorClassNames::LOAD_COMMAND_PROCESSOR_CLASS == proccessorType)
    {
        ret = createLoadCommandProcessorModel(modelName, commandName);
    }
    else if(observable::ProcessorClassNames::EXPECTED_VALUE_CHECK_COMMAND_PROCESSOR_CLASS == proccessorType)
    {
        ret = createCheckCommandProcessorModel(modelName, commandName);
    }
    else if(observable::ProcessorClassNames::EXPECTED_VALUE_NO_CHECK_COMMAND_PROCESSOR_CLASS == proccessorType)
    {
        ret = createNoCheckCommandProcessorModel(modelName, commandName);
    }

    return ret;
}

model::CommandProcessorModel *ObservableModelLoaderFactory::createLoadCommandProcessorModel(const model::ProcessorModelName &modelName,
                                                                                                  const command::CommandName &commandName)
{
    return new model::LoadCommandProcessorModel{modelName, commandName};
}

model::CommandProcessorModel *ObservableModelLoaderFactory::createCheckCommandProcessorModel(const model::ProcessorModelName &modelName,
                                                                                                   const command::CommandName &commandName)
{
    return new model::ExpectedValueCheckCommandProcessorModel{modelName, commandName};
}

model::CommandProcessorModel *ObservableModelLoaderFactory::createNoCheckCommandProcessorModel(const model::ProcessorModelName &modelName,
                                                                                                     const command::CommandName &commandName)
{
    return new model::ExpectedValueNoCheckCommandProcessorModel{modelName, commandName};
}

model::ObservableModel *ObservableModelLoaderFactory::createObservableModel(const model::ObservableModelName &name,
                                                                                  const observable::ObservableType &className)
{
    model::ObservableModel  *ret{nullptr};

    if (observable::ObservableClassNames::LOAD_CLASS == className)
    {
        ret = createLoadObservableModel(name);
    }
    else if (observable::ObservableClassNames::ACTUATOR_CLASS == className)
    {
        ret = createActuatorObservableModel(name);
    }
    else if (observable::ObservableClassNames::SENSOR_CLASS == className)
    {
        ret = createSensorObservableModel(name);
    }

    return ret;
}

model::ObservableModel *ObservableModelLoaderFactory::createLoadObservableModel(const model::ObservableModelName &modelName)
{
    return new model::LoadModel{modelName};
}

model::ObservableModel *ObservableModelLoaderFactory::createActuatorObservableModel(const model::ObservableModelName &modelName)
{
    return new model::ActuatorModel{modelName};
}

model::ObservableModel *ObservableModelLoaderFactory::createSensorObservableModel(const model::ObservableModelName &modelName)
{
    return new model::SensorModel{modelName};
}
