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
#include "event/mandatorypropertiesmodelloadingevent.h"
#include "event/specificpropertiesmodelloadingevent.h"
#include "event/processorsmodelloadingevent.h"
#include "event/observablemodelsloadingevent.h"
#include "observable/property/property.h"
#include "observable/property/propertyid.h"
#include "observable/property/propertyclassnames.h"
#include "observable/property/lowproperty.h"
#include "model/property/propertymodelnames.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablemodel.h"
#include "observablemodelloaderlistener.h"
#include "observablemodelloaderemitter.h"
#include "observablemodelloader.h"
#include "observablemodelloaderfactory.h"

using namespace elekdom::oplink::observablemodelloader::bundle;
using namespace elekdom::oplink::core;
using namespace elekdom::oplink;

ObservableModelLoaderListener::ObservableModelLoaderListener(Bundle& bundle, QObject *parent):
    BundleListener{bundle,parent}
{

}

ObservableModelLoaderListener::~ObservableModelLoaderListener()
{

}

void ObservableModelLoaderListener::onEvent(plugframe::core::event::QspEvent ev)
{
    plugframe::core::event::Event* event{ev.data()};
    QString evtTypeId {ev->getTypeId()};

    if (evtTypeId == MandatoryPropertiesModelLoadingEvent::s_typeId)
    {
        onMandatoryPropertiesModelLoadingEvent(dynamic_cast<MandatoryPropertiesModelLoadingEvent*>(event));
    }
    else if (evtTypeId == SpecificPropertiesModelLoadingEvent::s_typeId)
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

void ObservableModelLoaderListener::onMandatoryPropertiesModelLoadingEvent(MandatoryPropertiesModelLoadingEvent *event)
{
    if (event)
    {
        switch(event->cpt())
        {
            case 1:
                    mandatoryPropertiesModelLoadingLoop1();
                    break;
            case 2:
                    mandatoryPropertiesModelLoadingLoop2();
                    break;
            case 3:
                    mandatoryPropertiesModelLoadingLoop3();
                    break;
            default:
                    mandatoryPropertiesModelLoadingLoop4();
        }
    }
}

void ObservableModelLoaderListener::onSpecificPropertiesModelLoadingEvent(SpecificPropertiesModelLoadingEvent *event)
{
    if (event)
    {
        ObservableModelLoader& bundle{getObservableModelLoaderBundle()};
        quint16 modelIdx;
        bool hasNext;
        core::model::PropertyModelName modelName;
        core::observable::PropertyName propertyName;
        core::observable::PropertyType propertyClassName;
        QVariant::Type valueType;

        modelIdx = event->cpt() - 1;
        hasNext = bundle.nextPropertyModelDeclaration(modelIdx,
                                                      modelName,
                                                      propertyName,
                                                      propertyClassName,
                                                      valueType);
        if (hasNext)
        {
            if (!buildRegisterPropertyModel(modelName,propertyName,propertyClassName,valueType))
            {
                pfWarning1(getLogBundleName()) << tr("Erreur à l'enregistrement du modèle de propriété : %1 %2 %3 %4").arg(modelName, propertyName, propertyClassName).arg(valueType);
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
        core::model::ProcessorModelName modelName;
        core::command::CommandName commandName;
        core::observable::ProcessorType processorClassName;

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
        core::model::ObservableModelName modelName;
        core::observable::ObservableType observableClassName;
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
            factory::ObservableModelLoaderFactory& modelLoaderFactory{dynamic_cast<factory::ObservableModelLoaderFactory&>(getFactory())};

            // Create an observable model
            oplink::core::model::QspObservableModel observableModel{modelLoaderFactory.createObservableModel(modelName,observableClassName)};

            if(observableModel.isNull())
            {
                pfWarning1(getLogBundleName()) << tr("Erreur de création du modèle :%1 %2 ").arg(modelName, observableClassName);
            }
            else
            {
                // Set the model's properties
                //---------------------------

                // Mandatory properties
                setMandatoryProperties(observableModel);

                // Specific properties
                oplink::core::model::QspObservablePropertyModel propertyModel;
                for (int i = 0; i < propertyModelRefs.size(); ++i)
                {
                    propertyModel = modelRegisterService()->getPropertyModel(propertyModelRefs.at(i));
                    observableModel->addPropertyModelRef(propertyModel);
                }

                // Set the model's processors
                //---------------------------

                oplink::core::model::QspCommandProcessorModel processorModel;
                for (int i = 0; i < processorModelRefs.size(); ++i)
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

void ObservableModelLoaderListener::mandatoryPropertiesModelLoadingLoop1()
{
    pfDebug3(getLogBundleName()) << "->mandatoryPropertiesModelLoadingLoop1";

    buildRegisterPropertyModel(model::PropertyModelNames::MODEL_P_NAME,
                               observable::PropertyId::P_NAME,
                               observable::PropertyClassNames::PROPERTY_CLASS,
                               QVariant::String);

    mandatoryPropertiesModelEventLoop(2);

    pfDebug3(getLogBundleName()) << "<-mandatoryPropertiesModelLoadingLoop1";
}

void ObservableModelLoaderListener::mandatoryPropertiesModelLoadingLoop2()
{
    pfDebug3(getLogBundleName()) << "->mandatoryPropertiesModelLoadingLoop2";

    buildRegisterPropertyModel(model::PropertyModelNames::MODEL_P_OMODEL,
                               observable::PropertyId::P_MODEL,
                               observable::PropertyClassNames::PROPERTY_CLASS,
                               QVariant::String);

    mandatoryPropertiesModelEventLoop(3);

    pfDebug3(getLogBundleName()) << "<-mandatoryPropertiesModelLoadingLoop2";
}

void ObservableModelLoaderListener::mandatoryPropertiesModelLoadingLoop3()
{
    pfDebug3(getLogBundleName()) << "->mandatoryPropertiesModelLoadingLoop3";

    buildRegisterPropertyModel(model::PropertyModelNames::MODEL_P_LOCALISATION,
                               observable::PropertyId::P_LOCALISATION,
                               observable::PropertyClassNames::PROPERTY_CLASS,
                               QVariant::String);

    mandatoryPropertiesModelEventLoop(4);

    pfDebug3(getLogBundleName()) << "<-mandatoryPropertiesModelLoadingLoop3";
}

void ObservableModelLoaderListener::mandatoryPropertiesModelLoadingLoop4()
{
    pfDebug3(getLogBundleName()) << "->mandatoryPropertiesModelLoadingLoop4";

    specificPropertiesModelEventLoop(1);

    pfDebug3(getLogBundleName()) << "<-mandatoryPropertiesModelLoadingLoop4";
}

void ObservableModelLoaderListener::mandatoryPropertiesModelEventLoop(quint16 cpt)
{
    pfDebug3(getLogBundleName()) << "->mandatoryPropertiesModelEventLoop";

    loaderEmitter()->mandatoryPropertiesModelEventLoop(cpt);

    pfDebug3(getLogBundleName()) << "<-mandatoryPropertiesModelEventLoop";
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

bool ObservableModelLoaderListener::buildRegisterPropertyModel(const model::PropertyModelName& modelName,
                                                                  const observable::PropertyName &propertyId,
                                                                  const observable::PropertyType &propertyType,
                                                                  QVariant::Type valueType)
{
    // Builds property model
    model::QspObservablePropertyModel propertyModel{loaderFactory().createObservablePropertyModel(modelName, propertyId, propertyType, valueType)};

    // Registers model
    return modelRegisterService()->addPropertyModel(propertyModel);
}

bool ObservableModelLoaderListener::buildRegisterProcessorModel(const model::ProcessorModelName &modelName,
                                                                   const command::CommandName &cmdName,
                                                                   const observable::ProcessorType &processorType)
{
    // Builds processor model
    model::QspCommandProcessorModel processorModel{loaderFactory().createCommandProcessorModel(modelName, cmdName, processorType)};

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

observablemodelloader::factory::ObservableModelLoaderFactory& ObservableModelLoaderListener::loaderFactory()
{
    ObservableModelLoader& loaderBundle{dynamic_cast<ObservableModelLoader&>(getBundle())};
    return dynamic_cast<factory::ObservableModelLoaderFactory&>(loaderBundle.getFactory());
}

observablemodelregister::service::ModelRegisterServiceInterface *observablemodelloader::bundle::ObservableModelLoaderListener::modelRegisterService()
{
    ObservableModelLoader& loaderBundle{dynamic_cast<ObservableModelLoader&>(getBundle())};
    return loaderBundle.modelRegisterService();
}

void observablemodelloader::bundle::ObservableModelLoaderListener::setMandatoryProperties(model::QspObservableModel &observableModel)
{
    model::QspObservablePropertyModel propertyModel = modelRegisterService()->getPropertyModel(model::PropertyModelNames::MODEL_P_NAME);
    observableModel->addPropertyModelRef(propertyModel);

    propertyModel = modelRegisterService()->getPropertyModel(model::PropertyModelNames::MODEL_P_OMODEL);
    observableModel->addPropertyModelRef(propertyModel);

    propertyModel = modelRegisterService()->getPropertyModel(model::PropertyModelNames::MODEL_P_LOCALISATION);
    observableModel->addPropertyModelRef(propertyModel);
}

ObservableModelLoader &ObservableModelLoaderListener::getObservableModelLoaderBundle()
{
    return dynamic_cast<ObservableModelLoader&>(getBundle());
}
