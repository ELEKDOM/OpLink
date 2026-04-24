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
#include "observablemodelloaderemitter.h"
#include "observablemodelloader_forward.h"

class ObservableModelLoaderListener : public plugframe::BundleListener
{
public:
    ObservableModelLoaderListener(plugframe::Bundle& bundle, QObject *parent = nullptr);
    ~ObservableModelLoaderListener() override;

protected:
    void onEvent(plugframe::QspEvent ev) override;
    virtual void onSpecificPropertiesModelLoadingEvent(SpecificPropertiesModelLoadingEvent *event);
    virtual void onProcessorsModelLoadingEvent(ProcessorsModelLoadingEvent *event);
    virtual void onObservableModelsLoadingEvent(ObservableModelsLoadingEvent *event);
    void specificPropertiesModelEventLoop(quint16 cpt);
    void processorModelEventLoop(quint16 cpt);
    void observableModelsEventLoop(quint16 cpt);
    bool buildRegisterPropertyModel(const oplink::PropertyModelName& modelName,
                                    const oplink::PropertyName& propertyId,
                                    const oplink::PropertyType& propertyType);
    bool buildRegisterProcessorModel(const oplink::ProcessorModelName& modelName,
                                     const oplink::CommandName& cmdName,
                                     const oplink::ProcessorType& processorType);
    void observableModelsLoadingLoopEnd();
    QspObservableModelLoaderEmitter loaderEmitter();
    ObservableModelLoaderFactory& loaderFactory();
    oplink::ModelRegisterServiceInterface *modelRegisterService();

private:
    ObservableModelLoader &getObservableModelLoaderBundle();
};

#endif // OBSERVABLEMODELLOADERLISTENER_H
