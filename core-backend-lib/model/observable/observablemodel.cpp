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

#include "observablemodel.h"
#include "model/modellogchannel.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablebuilderargs.h"
#include "logger/pflog.h"
#include "observable/observable/observablebuilder.h"
#include "observable/property/propertyid.h"

oplink::ObservableModel::ObservableModel(const oplink::ObservableModelName& name):
    plugframe::Loggable{s_ModelLogChannel},
    m_modelName{name}
{
    pfDebug1(logChannel()) << "->ObservableModel::ObservableModel, " << name;

    pfDebug1(logChannel()) << "<-ObservableModel::ObservableModel";
}

oplink::ObservableModel::~ObservableModel()
{

}

void oplink::ObservableModel::addPropertyModelRef(oplink::QspObservablePropertyModel ref)
{
    m_propertyModelRefs.append(ref);
}

void oplink::ObservableModel::addProcessorModelRef(oplink::QspCommandProcessorModel ref)
{
    m_processorModelRefs.append(ref);
}

oplink::QspObservableBuilder oplink::ObservableModel::buildObservable(QspObservableBuilderArgs builderArgs)
{
    pfDebug3(logChannel()) << "->ObservableModel::buildObservable [" << m_modelName << "]";

    oplink::QspObservableBuilder newObservable;

    if (checkBuilderArgs(builderArgs))
    {
        newObservable.reset(createInstance(builderArgs));
        if (!newObservable.isNull())
        {
            if (buildProperties(newObservable, builderArgs))
            {
                buildProcessors(newObservable, builderArgs);
            }

            postBuild(newObservable, builderArgs);
        }
    }

    if (newObservable.isNull())
    {
        pfWarning1(logChannel()) << QObject::tr("Echec de création d'un Observable. Modèle ") << m_modelName;
    }

    pfDebug3(logChannel()) << "<-ObservableModel::buildObservable, newObservable " << newObservable;

    return newObservable;
}

bool oplink::ObservableModel::buildProperties(oplink::QspObservableBuilder observableBuilder,
                                              oplink::QspObservableBuilderArgs builderArgs)
{
    bool ret{createProperties(observableBuilder)};

    if (ret)
    {
        ret = setPropertyMandatoryValues(observableBuilder, builderArgs);
    }

    return ret;
}

bool oplink::ObservableModel::setPropertyMandatoryValues(oplink::QspObservableBuilder observableBuilder,
                                                         oplink::QspObservableBuilderArgs builderArgs)
{
    bool ret, ret1,ret2,ret3;

    ret1 = observableBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_NAME, builderArgs->m_observableName);
    ret2 = observableBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_MODEL, m_modelName);
    ret3 = observableBuilder->setMandatoryPropertyValue(oplink::PropertyId::P_LOCALISATION,builderArgs->m_observableLocalisation);
    ret = ret1 && ret2 && ret3;

    return ret;
}

void oplink::ObservableModel::postBuild(oplink::QspObservableBuilder observableBuilder,
                                        oplink::QspObservableBuilderArgs builderArgs)
{
    Q_UNUSED(observableBuilder)
    Q_UNUSED(builderArgs)
    // No OP!
}

bool oplink::ObservableModel::createProperties(oplink::QspObservableBuilder observableBuilder)
{
    bool ret{true};
    oplink::Observable& parent{observableBuilder->toObservable()};
    QListIterator<oplink::QspObservablePropertyModel> it{m_propertyModelRefs};

    while(it.hasNext() && ret)
    {
        oplink::QspObservablePropertyModel propertyModel{it.next()};

        oplink::Property* ptrProperty{propertyModel->createProperty(parent)};

        if (ptrProperty != nullptr)
        { 
            observableBuilder->addProperty(ptrProperty);
        }
        else
        {
            ret = false;
            pfWarning1(logChannel()) << QObject::tr("Echec de création d'une Property. Modèle ") << propertyModel->modelName();
        }
    }

    return ret;
}

bool oplink::ObservableModel::buildProcessors(oplink::QspObservableBuilder observableBuilder,
                                              oplink::QspObservableBuilderArgs builderArgs)
{
    bool ret{true};
    oplink::Observable& parent{observableBuilder->toObservable()};
    QListIterator<oplink::QspCommandProcessorModel> it{m_processorModelRefs};

    while(it.hasNext() && ret)
    {
        oplink::QspCommandProcessorModel processorModel{it.next()};
        oplink::CommandProcessor* ptrProcessor{processorModel->createProcessor(parent, builderArgs)};

        if (ptrProcessor != nullptr)
        {
            observableBuilder->addProcessor(ptrProcessor);
        }
        else
        {
            ret = false;
            pfWarning1(logChannel()) << QObject::tr("Echec de création d'un CommandProcessor. Modèle ") << processorModel->modelName();
        }
    }
    return ret;
}




