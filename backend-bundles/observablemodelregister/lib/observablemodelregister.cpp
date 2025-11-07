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

#include <QMutexLocker>
#include "logger/pflog.h"
#include "service-int/modelregisterserviceinterface.h"
#include "service-int/observablebuilderserviceinterface.h"
#include "model/observable/observablemodel.h"
#include "model/observable/observablebuilderargs.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "observable/observable/observablebuilder.h"
#include "observablemodelregister.h"
#include "observablemodelregisterfactory.h"

ObservableModelRegister::ObservableModelRegister():
    plugframe::BundleImplementation{"ObservableModelRegister"}
{
}

ObservableModelRegister::~ObservableModelRegister()
{
    m_propertyModels.clear();
    m_processorModels.clear();
    m_observableModels.clear();
}

oplink::QspObservableModel ObservableModelRegister::getObservableModel(const oplink::ObservableModelName& modelName)
{
    oplink::QspObservableModel ret;

    if (m_observableModels.contains(modelName))
    {
        ret = m_observableModels.value(modelName);
    }

    return ret;
}

bool ObservableModelRegister::addPropertyModel(oplink::QspObservablePropertyModel model)
{
    QMutexLocker        locker(&m_mutex);
    bool                ret{false};
    const oplink::PropertyModelName& id{model->modelName()};

    if (!m_propertyModels.contains(id))
    {
        pfInfo1(logChannel()) << QObject::tr("Ajout du model de property : ") << model->modelName();
        m_propertyModels.insert(id, model);
        ret = true;
    }

    return ret;
}

oplink::QspObservablePropertyModel ObservableModelRegister::getPropertyModel(oplink::PropertyModelName id)
{
    QMutexLocker locker(&m_mutex);

    return m_propertyModels.value(id);
}

bool ObservableModelRegister::addProcessorModel(oplink::QspCommandProcessorModel model)
{
    QMutexLocker                      locker(&m_mutex);
    bool                              ret{false};
    const oplink::ProcessorModelName& id{model->modelName()};

    if (!m_processorModels.contains(id))
    {
        pfInfo1(logChannel()) << QObject::tr("Ajout du model de processor : ") << model->modelName();
        m_processorModels.insert(id, model);
        ret = true;
    }

    return ret;
}

oplink::QspCommandProcessorModel ObservableModelRegister::getProcessorModel(oplink::ProcessorModelName id)
{
    QMutexLocker locker(&m_mutex);

    return m_processorModels.value(id);
}

bool ObservableModelRegister::addObservableModel(oplink::QspObservableModel model)
{
    QMutexLocker    locker(&m_mutex);
    bool            ret{false};

    if (!m_observableModels.contains(model->modelName()))
    {
        pfInfo1(logChannel()) << QObject::tr("Ajout du model d'observable : ") << model->modelName();
        m_observableModels.insert(model->modelName(), model);
        ret = true;
    }

    return ret;
}

oplink::QspObservableBuilder ObservableModelRegister::buildObservable(oplink::QspObservableBuilderArgs builderargs)
{
    pfInfo2(logChannel()) << "buildObservable : observableName = " << builderargs->m_observableName << ", observableModelName = " << builderargs->m_observableModelName << ", observableLocalisation = " << builderargs->m_observableLocalisation;
    QMutexLocker                 locker(&m_mutex);
    oplink::QspObservableModel   observableModel{getObservableModel(builderargs->m_observableModelName)};
    oplink::QspObservableBuilder newObs;

    if (!observableModel.isNull())
    {
        newObs = observableModel->buildObservable(builderargs);
    }

    return newObs;
}

plugframe::BundleFactory *ObservableModelRegister::createFactory()
{
    return new ObservableModelRegisterFactory;
}

plugframe::ServiceInterface *ObservableModelRegister::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (oplink::ModelRegisterServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<oplink::ModelRegisterServiceInterface*>(getQplugin());
    }
    else if (oplink::ObservableBuilderServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<oplink::ObservableBuilderServiceInterface*>(getQplugin());
    }

    return ret;
}


