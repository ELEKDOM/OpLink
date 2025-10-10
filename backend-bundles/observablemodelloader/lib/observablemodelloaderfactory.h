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
#include "command/command-names.h"
#include "olcore-backend-lib_forward.h"
#include "observablemodelloader_forward.h"

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace observablemodelloader
{
namespace factory
{

class ObservableModelLoaderFactory : public plugframe::core::bundle::BundleFactory
{
public:
    ObservableModelLoaderFactory();
    ~ObservableModelLoaderFactory() override;

public:
    virtual MandatoryPropertiesModelLoadingEvent *createMandatoryPropertiesModelLoadingEvent(unsigned short cpt);
    virtual SpecificPropertiesModelLoadingEvent *createSpecificPropertiesModelLoadingEvent(unsigned short cpt);
    virtual ProcessorsModelLoadingEvent *createProcessorsModelLoadingEvent(unsigned short cpt);
    virtual ObservableModelsLoadingEvent *createObservableModelsLoadingEvent(unsigned short cpt);
    virtual model::ObservablePropertyModel *createObservablePropertyModel(const model::PropertyModelName& modelName,
                                                                             const observable::PropertyName& propertyId,
                                                                             const observable::PropertyType& propertyType,
                                                                             QVariant::Type valueType);
    virtual model::ObservablePropertyModel *createPropertyModel(const model::PropertyModelName& modelName,
                                                                   const observable::PropertyName& propertyId,
                                                                   QVariant::Type valueType);
    virtual model::ObservablePropertyModel *createLoadPropertyModel(const model::PropertyModelName& modelName,
                                                                       const observable::PropertyName& propertyId,
                                                                       QVariant::Type valueType);
    virtual model::ObservablePropertyModel *createActuatorPropertyModel(const model::PropertyModelName& modelName,
                                                                           const observable::PropertyName& propertyId,
                                                                           QVariant::Type valueType);
    virtual model::ObservablePropertyModel *createSensorPropertyModel(const model::PropertyModelName& modelName,
                                                                         const observable::PropertyName& propertyId,
                                                                         QVariant::Type valueType);
    virtual model::CommandProcessorModel *createCommandProcessorModel(const model::ProcessorModelName& modelName,
                                                                         const command::CommandName& commandName,
                                                                         const observable::ProcessorType& proccessorType);
    virtual model::CommandProcessorModel *createLoadCommandProcessorModel(const model::ProcessorModelName& modelName,
                                                                             const command::CommandName& commandName);
    virtual model::CommandProcessorModel *createCheckCommandProcessorModel(const model::ProcessorModelName& modelName,
                                                                              const command::CommandName& commandName);
    virtual model::CommandProcessorModel *createNoCheckCommandProcessorModel(const model::ProcessorModelName& modelName,
                                                                                const command::CommandName& commandName);
    virtual model::ObservableModel *createObservableModel(const model::ObservableModelName& modelName,
                                                             const observable::ObservableType& className);
    virtual model::ObservableModel *createLoadObservableModel(const model::ObservableModelName& modelName);
    virtual model::ObservableModel *createActuatorObservableModel(const model::ObservableModelName& modelName);
    virtual model::ObservableModel *createSensorObservableModel(const model::ObservableModelName& modelName);

protected:
    PF_createServiceImplementation_DECL
    BundleEmitter *createBundleEmitter(Bundle& myBundle) override;
    BundleListener *createBundleListener(Bundle& myBundle) override;
};

}//namespace factory
}//namespace observablemodelloader
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEMODELLOADERFACTORY_H
