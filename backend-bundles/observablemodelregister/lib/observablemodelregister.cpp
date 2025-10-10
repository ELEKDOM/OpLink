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
#include "bundle/bundlecontext.h"
#include "model/observable/observablemodel.h"
#include "model/observable/observablebuilderargs.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "observable/observable/observablebuilder.h"
#include "observablemodelregister.h"
#include "observablemodelregisterfactory.h"

using namespace elekdom::oplink::observablemodelregister::bundle;
using namespace elekdom::oplink::core;

ObservableModelRegister::ObservableModelRegister():
    plugframe::core::bundle::BundleImplementation{"ObservableModelRegister"}
{
}

ObservableModelRegister::~ObservableModelRegister()
{
    m_propertyModels.clear();
    m_processorModels.clear();
    m_observableModels.clear();
}

model::QspObservableModel ObservableModelRegister::getObservableModel(const model::ObservableModelName& modelName)
{
    model::QspObservableModel ret;

    if (m_observableModels.contains(modelName))
    {
        ret = m_observableModels.value(modelName);
    }

    return ret;
}

bool ObservableModelRegister::addPropertyModel(model::QspObservablePropertyModel model)
{
    QMutexLocker        locker(&m_mutex);
    bool                ret{false};
    const model::PropertyModelName& id{model->modelName()};

    if (!m_propertyModels.contains(id))
    {
        pfInfo1(logChannel()) << QObject::tr("Ajout du model de property : ") << model->modelName();
        m_propertyModels.insert(id, model);
        ret = true;
    }

    return ret;
}

model::QspObservablePropertyModel ObservableModelRegister::getPropertyModel(model::PropertyModelName id)
{
    QMutexLocker locker(&m_mutex);

    return m_propertyModels.value(id);
}

bool ObservableModelRegister::addProcessorModel(model::QspCommandProcessorModel model)
{
    QMutexLocker                locker(&m_mutex);
    bool                        ret{false};
    const model::ProcessorModelName& id{model->modelName()};

    if (!m_processorModels.contains(id))
    {
        pfInfo1(logChannel()) << QObject::tr("Ajout du model de processor : ") << model->modelName();
        m_processorModels.insert(id, model);
        ret = true;
    }

    return ret;
}

model::QspCommandProcessorModel ObservableModelRegister::getProcessorModel(model::ProcessorModelName id)
{
    QMutexLocker locker(&m_mutex);

    return m_processorModels.value(id);
}

bool ObservableModelRegister::addObservableModel(model::QspObservableModel model)
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

observable::QspObservableBuilder ObservableModelRegister::buildObservable(model::QspObservableBuilderArgs builderargs)
{
    pfInfo2(logChannel()) << "buildObservable : observableName = " << builderargs->m_observableName << ", observableModelName = " << builderargs->m_observableModelName << ", observableLocalisation = " << builderargs->m_observableLocalisation;
    QMutexLocker                     locker(&m_mutex);
    model::QspObservableModel        observableModel{getObservableModel(builderargs->m_observableModelName)};
    observable::QspObservableBuilder newObs;

    if (!observableModel.isNull())
    {
        newObs = observableModel->buildObservable(builderargs);
    }

    return newObs;
}

elekdom::plugframe::core::bundle::BundleFactory *ObservableModelRegister::createFactory()
{
    return new factory::ObservableModelRegisterFactory;
}

plugin::ServiceInterface *ObservableModelRegister::qtServiceInterface(const QString &sName)
{
    plugframe::core::plugin::ServiceInterface *ret{nullptr};

    if (service::ModelRegisterServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<service::ModelRegisterServiceInterface*>(getQplugin());
    }
    else if (service::ObservableBuilderServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<service::ObservableBuilderServiceInterface*>(getQplugin());
    }

    return ret;
}


