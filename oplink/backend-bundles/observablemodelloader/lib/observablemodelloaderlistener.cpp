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

#include "logger/pflog.h"
#include "event/event.h"
#include "event/specificpropertiesmodelloadingevent.h"
#include "event/processorsmodelloadingevent.h"
#include "event/observablemodelsloadingevent.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablemodel.h"
#include "observablemodelloaderlistener.h"
#include "observablemodelloader.h"
#include "observablemodelloaderfactory.h"

ObservableModelLoaderListener::ObservableModelLoaderListener(plugframe::Bundle& bundle, QObject *parent):
    plugframe::BundleListener{bundle,parent}
{

}

ObservableModelLoaderListener::~ObservableModelLoaderListener()
{

}

void ObservableModelLoaderListener::onEvent(plugframe::QspEvent ev)
{
    plugframe::Event* event{ev.data()};
    QString evtTypeId {ev->getTypeId()};

    if (evtTypeId == SpecificPropertiesModelLoadingEvent::s_typeId)
    {
        onSpecificPropertiesModelLoadingEvent(dynamic_cast<SpecificPropertiesModelLoadingEvent*>(event));
    }
    else if (evtTypeId == ProcessorsModelLoadingEvent::s_typeId)
    {
        onProcessorsModelLoadingEvent(dynamic_cast<ProcessorsModelLoadingEvent*>(event));
    }
    else if (evtTypeId == ObservableModelsLoadingEvent::s_typeId)
    {
        onObservableModelsLoadingEvent(dynamic_cast<ObservableModelsLoadingEvent*>(event));
    }
}

void ObservableModelLoaderListener::onSpecificPropertiesModelLoadingEvent(SpecificPropertiesModelLoadingEvent *event)
{
    if (event)
    {
        ObservableModelLoader& bundle{getObservableModelLoaderBundle()};
        quint16 modelIdx;
        bool hasNext;
        oplink::PropertyModelName modelName;
        oplink::PropertyName propertyName;
        oplink::PropertyType propertyClassName;

        modelIdx = event->cpt() - 1;
        hasNext = bundle.nextPropertyModelDeclaration(modelIdx,
                                                      modelName,
                                                      propertyName,
                                                      propertyClassName);
        if (hasNext)
        {
            if (!buildRegisterPropertyModel(modelName,propertyName,propertyClassName))
            {
                pfWarning1(getLogBundleName()) << tr("Erreur à l'enregistrement du modèle de propriété : %1 %2 %3").arg(modelName, propertyName, propertyClassName);
            }
            specificPropertiesModelEventLoop(modelIdx + 2);
        }
        else
        {
            processorModelEventLoop(1);
        }
    }
}

void ObservableModelLoaderListener::onProcessorsModelLoadingEvent(ProcessorsModelLoadingEvent *event)
{
    if (event)
    {
        ObservableModelLoader& bundle{getObservableModelLoaderBundle()};
        quint16 modelIdx;
        bool hasNext;
        oplink::ProcessorModelName modelName;
        oplink::CommandName commandName;
        oplink::ProcessorType processorClassName;

        modelIdx = event->cpt() - 1;
        hasNext = bundle.nextProcessorModelDeclaration(modelIdx,
                                                       modelName,
                                                       commandName,
                                                       processorClassName);
        if(hasNext)
        {
            if (!buildRegisterProcessorModel(modelName,commandName,processorClassName))
            {
                pfWarning1(getLogBundleName()) << tr("Erreur à l'enregistrement du modèle de traitement d'une commande : %1 %2 %3").arg(modelName, commandName, processorClassName);
            }
            processorModelEventLoop(modelIdx + 2);
        }
        else
        {
            observableModelsEventLoop(1);
        }
    }
}

void ObservableModelLoaderListener::onObservableModelsLoadingEvent(ObservableModelsLoadingEvent *event)
{
    if (event)
    {
        ObservableModelLoader& bundle{getObservableModelLoaderBundle()};
        quint16 modelIdx;
        bool hasNext;
        oplink::ObservableModelName modelName;
        oplink::ObservableType observableClassName;
        QStringList propertyModelRefs;
        QStringList processorModelRefs;

        modelIdx = event->cpt() - 1;
        hasNext = bundle.nextObservableModelDeclaration(modelIdx,
                                                        modelName,
                                                        observableClassName,
                                                        propertyModelRefs,
                                                        processorModelRefs);
        if (hasNext)
        {
            ObservableModelLoaderFactory& modelLoaderFactory{dynamic_cast<ObservableModelLoaderFactory&>(getFactory())};

            // Create an observable model
            oplink::QspObservableModel observableModel{modelLoaderFactory.createObservableModel(modelName,observableClassName)};

            if(observableModel.isNull())
            {
                pfWarning1(getLogBundleName()) << tr("Erreur de création du modèle :%1 %2 ").arg(modelName, observableClassName);
            }
            else
            {
                // Set the model's properties
                //---------------------------
                oplink::QspObservablePropertyModel propertyModel;
                for (auto i = 0; i < propertyModelRefs.size(); ++i)
                {
                    propertyModel = modelRegisterService()->getPropertyModel(propertyModelRefs.at(i));
                    observableModel->addPropertyModelRef(propertyModel);
                }

                // Set the model's processors
                //---------------------------

                oplink::QspCommandProcessorModel processorModel;
                for (auto i = 0; i < processorModelRefs.size(); ++i)
                {
                    processorModel = modelRegisterService()->getProcessorModel(processorModelRefs.at(i));
                    observableModel->addProcessorModelRef(processorModel);
                }

                // Register the model
                //-------------------

                if (!modelRegisterService()->addObservableModel(observableModel))
                {
                    pfWarning1(getLogBundleName()) << tr("Erreur à l'enregistrement du modèle d'observable : %1 %2").arg(modelName,observableClassName);
                }

                // Next modele to load
                observableModelsEventLoop(modelIdx + 2);
            }
        }
        else
        {
            observableModelsLoadingLoopEnd();
        }
    }
}

void ObservableModelLoaderListener::specificPropertiesModelEventLoop(quint16 cpt)
{
    pfDebug3(getLogBundleName()) << "->specificPropertiesModelEventLoop";

    loaderEmitter()->specificPropertiesModelEventLoop(cpt);

    pfDebug3(getLogBundleName()) << "<-specificPropertiesModelEventLoop";
}

void ObservableModelLoaderListener::processorModelEventLoop(quint16 cpt)
{
    pfDebug3(getLogBundleName()) << "->processorModelEventLoop, " << cpt;

    loaderEmitter()->processorModelEventLoop(cpt);

    pfDebug3(getLogBundleName()) << "<-processorModelEventLoop";
}

void ObservableModelLoaderListener::observableModelsEventLoop(quint16 cpt)
{
    pfDebug3(getLogBundleName()) << "->observableModelsEventLoop, " << cpt;

    loaderEmitter()->observableModelsEventLoop(cpt);

    pfDebug3(getLogBundleName()) << "<-observableModelsEventLoop";
}

bool ObservableModelLoaderListener::buildRegisterPropertyModel(const oplink::PropertyModelName& modelName,
                                                               const oplink::PropertyName &propertyId,
                                                               const oplink::PropertyType &propertyType)
{
    // Builds property model
    oplink::QspObservablePropertyModel propertyModel{loaderFactory().createObservablePropertyModel(modelName, propertyId, propertyType)};

    // Registers model
    return modelRegisterService()->addPropertyModel(propertyModel);
}

bool ObservableModelLoaderListener::buildRegisterProcessorModel(const oplink::ProcessorModelName &modelName,
                                                                const oplink::CommandName &cmdName,
                                                                const oplink::ProcessorType &processorType)
{
    // Builds processor model
    oplink::QspCommandProcessorModel processorModel{loaderFactory().createCommandProcessorModel(modelName, cmdName, processorType)};

    // Registers model
    return modelRegisterService()->addProcessorModel(processorModel);
}

void ObservableModelLoaderListener::observableModelsLoadingLoopEnd()
{
    pfDebug3(getLogBundleName()) << "->observableModelsLoadingLoopEnd";

    // All Models are now loaded. Bundle is now started !
    ObservableModelLoader& loaderBundle{dynamic_cast<ObservableModelLoader&>(getBundle())};

    loaderBundle.started();

     pfDebug3(getLogBundleName()) << "<-observableModelsLoadingLoopEnd";
}

QspObservableModelLoaderEmitter ObservableModelLoaderListener::loaderEmitter()
{
    ObservableModelLoader& loaderBundle{dynamic_cast<ObservableModelLoader&>(getBundle())};

    return loaderBundle.emitter();
}

ObservableModelLoaderFactory& ObservableModelLoaderListener::loaderFactory()
{
    ObservableModelLoader& loaderBundle{dynamic_cast<ObservableModelLoader&>(getBundle())};
    return dynamic_cast<ObservableModelLoaderFactory&>(loaderBundle.getFactory());
}

oplink::ModelRegisterServiceInterface *ObservableModelLoaderListener::modelRegisterService()
{
    ObservableModelLoader& loaderBundle{dynamic_cast<ObservableModelLoader&>(getBundle())};
    return loaderBundle.modelRegisterService();
}

ObservableModelLoader &ObservableModelLoaderListener::getObservableModelLoaderBundle()
{
    return dynamic_cast<ObservableModelLoader&>(getBundle());
}
