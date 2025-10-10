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


#include <QFile>
#include "logger/pflog.h"
#include "bundle/bundlecontext.h"
#include "observablemodelloader.h"
#include "observablemodelloaderemitter.h"
#include "observablemodelloaderfactory.h"
#include "service-int/modelregisterserviceinterface.h"

using namespace elekdom::oplink::observablemodelloader::bundle;

ObservableModelLoader::ObservableModelLoader():
    plugframe::core::bundle::LongStartBundleImplementation{"ObservableModelLoader"}
{

}

ObservableModelLoader::~ObservableModelLoader()
{

}

QspObservableModelLoaderEmitter ObservableModelLoader::emitter()
{
    return getEmitter().dynamicCast<ObservableModelLoaderEmitter>();
}

elekdom::oplink::observablemodelregister::service::ModelRegisterServiceInterface *ObservableModelLoader::modelRegisterService()
{
    return bundleContext()->getService<elekdom::oplink::observablemodelregister::service::ModelRegisterServiceInterface>(elekdom::oplink::observablemodelregister::service::ModelRegisterServiceInterface::serviceName());
}

bool ObservableModelLoader::nextPropertyModelDeclaration(quint16 idx,
                                                            core::model::PropertyModelName &modelName,
                                                            core::observable::PropertyName &propertyName,
                                                            core::observable::PropertyType &propertyClassName,
                                                            QVariant::Type &valueType)
{
    bool ret{false};

    if ((idx >= 0) && (idx <  m_propertyModelNodes.size()))
    {
        QDomNode    node{m_propertyModelNodes.at(idx)};
        QDomElement modelElem{node.toElement()};
        QString     ptype;

        ret = true;
        modelName = modelElem.attribute(QStringLiteral("modelName"));
        propertyName = modelElem.attribute(QStringLiteral("propertyId"));
        propertyClassName = modelElem.attribute(QStringLiteral("propertyClass"));
        ptype = modelElem.attribute(QStringLiteral("propertyType"));

        if (QStringLiteral("bool") == ptype)
        {
            valueType = QVariant::Bool;
        }
        else if (QStringLiteral("uchar") == ptype)
        {
            valueType = QVariant::UInt;
        }
        else if (QStringLiteral("uint") == ptype)
        {
            valueType = QVariant::UInt;
        }
        else if (QStringLiteral("double") == ptype)
        {
            valueType = QVariant::Double;
        }
        else if (QStringLiteral("string") == ptype)
        {
            valueType = QVariant::String;
        }
        else
        {
            ret = false;
            pfErr(logChannel()) << QObject::tr("%1 type inconnu pour le modèle %2").arg(ptype, modelName);
        }
    }

    return ret;
}

bool ObservableModelLoader::nextProcessorModelDeclaration(quint16 idx,
                                                             core::model::ProcessorModelName &modelName,
                                                             core::command::CommandName &commandName,
                                                             core::observable::ProcessorType &processorClassName)
{
    bool ret{false};

    if ((idx >= 0) && (idx <  m_processorModelNodes.size()))
    {
        QDomNode    node{m_processorModelNodes.at(idx)};
        QDomElement modelElem{node.toElement()};

        ret = true;
        modelName = modelElem.attribute(QStringLiteral("modelName"));
        commandName = modelElem.attribute(QStringLiteral("commandName"));
        processorClassName = modelElem.attribute(QStringLiteral("processorClass"));
    }

    return ret;
}

bool ObservableModelLoader::nextObservableModelDeclaration(quint16 idx,
                                                              core::model::ObservableModelName &modelName,
                                                              core::observable::ObservableType &observableClassName,
                                                              QStringList &propertyModelRefs,
                                                              QStringList &processorModelRefs)
{
    bool ret{false};

    if ((idx >= 0) && (idx <  m_observableModelNodes.size()))
    {
        QDomNode     node{m_observableModelNodes.at(idx)};
        QDomElement  modelElem{node.toElement()};
        QDomNodeList propertyElemRefs{modelElem.elementsByTagName(QStringLiteral("propertyModelRef"))};
        QDomNodeList processorElemRefs{modelElem.elementsByTagName(QStringLiteral("processorModelRef"))};

        ret = true;
        modelName = modelElem.attribute(QStringLiteral("modelName"));
        observableClassName = modelElem.attribute(QStringLiteral("observableClass"));
        for (int i = 0; i < propertyElemRefs.length(); i++)
        {
            QDomNode    node{propertyElemRefs.at(i)};
            QDomElement elem{node.toElement()};

            propertyModelRefs << elem.attribute(QStringLiteral("modelName"));
        }
        for (int i = 0; i < processorElemRefs.length(); i++)
        {
            QDomNode    node{processorElemRefs.at(i)};
            QDomElement elem{node.toElement()};

            processorModelRefs << elem.attribute(QStringLiteral("modelName"));
        }
    }

    return ret;
}

BundleFactory *ObservableModelLoader::createFactory()
{
    return new factory::ObservableModelLoaderFactory;
}

void ObservableModelLoader::_start(QspBundleContext bundleContext)
{
    plugframe::core::bundle::LongStartBundleImplementation::_start(bundleContext);

    // Start models building and registering
    startModelsLoading();
}

PF_qtServiceInterface_DEF(ObservableModelLoader)

void ObservableModelLoader::startModelsLoading()
{
    pfDebug3(logChannel()) << "->ObservableModelLoader::startModelsLoading";

    if (loadModelDeclarations())
    {
        QspObservableModelLoaderEmitter loaderEmitter{getEmitter().dynamicCast<ObservableModelLoaderEmitter>()};
        loaderEmitter->startLoadingEventLoop();
    }

    pfDebug3(logChannel()) << "<-ObservableModelLoader::startModelsLoading";
}

bool ObservableModelLoader::loadModelDeclarations()
{
    bool ret;
    QString fileName(getConfPath());
    QFile file(fileName);

    pfDebug4(logChannel()) << "ObservableModelLoader::loadModelDeclarations, fichier à charger : " << fileName;

    ret = file.open(QIODevice::ReadOnly);
    if (ret)
    {
        ret = m_modelDeclarations.setContent(&file);
        file.close();

        if (ret)
        {
            m_propertyModelNodes   = m_modelDeclarations.elementsByTagName(QStringLiteral("property"));
            pfDebug4(logChannel()) << "ObservableModelLoader::loadModelDeclarations, m_propertyModelNodes.size() =  " << m_propertyModelNodes.size();
            m_processorModelNodes  = m_modelDeclarations.elementsByTagName(QStringLiteral("processor"));
            pfDebug4(logChannel()) << "ObservableModelLoader::loadModelDeclarations, m_processorModelNodes.size() =  " << m_processorModelNodes.size();
            m_observableModelNodes = m_modelDeclarations.elementsByTagName(QStringLiteral("observable"));
            pfDebug4(logChannel()) << "ObservableModelLoader::loadModelDeclarations, m_observableModelNodes.size() =  " << m_observableModelNodes.size();
        }
        else
        {
            pfWarning1(logChannel()) << QObject::tr("Erreur de format du fichier %1").arg(fileName);
        }
    }
    else
    {
        pfWarning1(logChannel()) << QObject::tr("Erreur d'ouverture du fichier %1").arg(fileName);
    }

    return ret;
}
