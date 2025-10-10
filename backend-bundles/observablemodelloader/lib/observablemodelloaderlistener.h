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

#ifndef OBSERVABLEMODELLOADERLISTENER_H
#define OBSERVABLEMODELLOADERLISTENER_H

#include "bundle/bundlelistener.h"
#include "model/modelnames.h"
#include "observable/observablenames.h"
#include "command/command-names.h"
#include "service-int/modelregisterserviceinterface.h"
#include "observablemodelloader_forward.h"
#include "olcore-backend-lib_forward.h"

using namespace elekdom::plugframe::core::bundle;
using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace observablemodelloader
{
namespace bundle
{

class ObservableModelLoaderListener : public BundleListener
{
public:
    ObservableModelLoaderListener(Bundle& bundle, QObject *parent = nullptr);
    ~ObservableModelLoaderListener() override;

protected:
    void onEvent(plugframe::core::event::QspEvent ev) override;
    virtual void onMandatoryPropertiesModelLoadingEvent(MandatoryPropertiesModelLoadingEvent *event);
    virtual void onSpecificPropertiesModelLoadingEvent(SpecificPropertiesModelLoadingEvent *event);
    virtual void onProcessorsModelLoadingEvent(ProcessorsModelLoadingEvent *event);
    virtual void onObservableModelsLoadingEvent(ObservableModelsLoadingEvent *event);
    void mandatoryPropertiesModelLoadingLoop1();
    void mandatoryPropertiesModelLoadingLoop2();
    virtual void mandatoryPropertiesModelLoadingLoop3();
    virtual void mandatoryPropertiesModelLoadingLoop4();
    void mandatoryPropertiesModelEventLoop(quint16 cpt);
    void specificPropertiesModelEventLoop(quint16 cpt);
    void processorModelEventLoop(quint16 cpt);
    void observableModelsEventLoop(quint16 cpt);
    bool buildRegisterPropertyModel(const model::PropertyModelName& modelName,
                                    const observable::PropertyName& propertyId,
                                    const observable::PropertyType& propertyType,
                                    QVariant::Type valueType);
    bool buildRegisterProcessorModel(const model::ProcessorModelName& modelName,
                                     const command::CommandName& cmdName,
                                     const observable::ProcessorType& processorType);
    void observableModelsLoadingLoopEnd();
    QSharedPointer<ObservableModelLoaderEmitter> loaderEmitter();
    factory::ObservableModelLoaderFactory& loaderFactory();
    observablemodelregister::service::ModelRegisterServiceInterface *modelRegisterService();
    virtual void setMandatoryProperties(model::QspObservableModel &observableModel);

private:
    ObservableModelLoader &getObservableModelLoaderBundle();
};

}//namespace bundle
}//namespace observablemodelloader
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEMODELLOADERLISTENER_H
