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

#ifndef OBSERVABLEMODELLOADERFACTORY_H
#define OBSERVABLEMODELLOADERFACTORY_H

#include "factory/bundlefactory.h"
#include "model/modelnames.h"
#include "observable/observablenames.h"
#include "observable/propertyid.h"
#include "command/command-names.h"
#include "event/specificpropertiesmodelloadingevent.h"
#include "event/processorsmodelloadingevent.h"
#include "event/observablemodelsloadingevent.h"
#include "olcore-backend-lib_forward.h"

class ObservableModelLoaderFactory : public plugframe::BundleFactory
{
public:
    ObservableModelLoaderFactory();
    ~ObservableModelLoaderFactory() override;

public:
    virtual SpecificPropertiesModelLoadingEvent *createSpecificPropertiesModelLoadingEvent(unsigned short cpt);
    virtual ProcessorsModelLoadingEvent *createProcessorsModelLoadingEvent(unsigned short cpt);
    virtual ObservableModelsLoadingEvent *createObservableModelsLoadingEvent(unsigned short cpt);
    virtual oplink::ObservablePropertyModel *createObservablePropertyModel(const oplink::PropertyModelName& modelName,
                                                                           const oplink::PropertyName& propertyId,
                                                                           const oplink::PropertyType& propertyType);
    virtual oplink::ObservablePropertyModel *createPropertyModel(const oplink::PropertyModelName& modelName,
                                                                 const oplink::PropertyName& propertyId);
    virtual oplink::ObservablePropertyModel *createLoadPropertyModel(const oplink::PropertyModelName& modelName,
                                                                     const oplink::PropertyName& propertyId);
    virtual oplink::ObservablePropertyModel *createActuatorPropertyModel(const oplink::PropertyModelName& modelName,
                                                                         const oplink::PropertyName& propertyId);
    virtual oplink::ObservablePropertyModel *createSensorPropertyModel(const oplink::PropertyModelName& modelName,
                                                                       const oplink::PropertyName& propertyId);
    virtual oplink::CommandProcessorModel *createCommandProcessorModel(const oplink::ProcessorModelName& modelName,
                                                                       const oplink::CommandName& commandName,
                                                                       const oplink::ProcessorType& proccessorType);
    virtual oplink::CommandProcessorModel *createLoadCommandProcessorModel(const oplink::ProcessorModelName& modelName,
                                                                           const oplink::CommandName& commandName);
    virtual oplink::CommandProcessorModel *createCheckCommandProcessorModel(const oplink::ProcessorModelName& modelName,
                                                                            const oplink::CommandName& commandName);
    virtual oplink::CommandProcessorModel *createNoCheckCommandProcessorModel(const oplink::ProcessorModelName& modelName,
                                                                              const oplink::CommandName& commandName);
    virtual oplink::ObservableModel *createObservableModel(const oplink::ObservableModelName& modelName,
                                                           const oplink::ObservableType& className);
    virtual oplink::ObservableModel *createLoadObservableModel(const oplink::ObservableModelName& modelName);
    virtual oplink::ObservableModel *createActuatorObservableModel(const oplink::ObservableModelName& modelName);
    virtual oplink::ObservableModel *createSensorObservableModel(const oplink::ObservableModelName& modelName);

protected:
    PF_createServiceImplementation_DECL
    plugframe::BundleEmitter *createBundleEmitter(plugframe::Bundle& myBundle) override;
    plugframe::BundleListener *createBundleListener(plugframe::Bundle& myBundle) override;
};

#endif // OBSERVABLEMODELLOADERFACTORY_H
