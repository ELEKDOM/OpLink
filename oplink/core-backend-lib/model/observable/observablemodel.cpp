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

oplink::ObservableModel::ObservableModel(const ObservableModelName& name):
    plugframe::Loggable{s_ModelLogChannel},
    m_modelName{name}
{
    pfDebug1(logChannel()) << "->ObservableModel::ObservableModel, " << name;

    pfDebug1(logChannel()) << "<-ObservableModel::ObservableModel";
}

oplink::ObservableModel::~ObservableModel()
{

}

void oplink::ObservableModel::addPropertyModelRef(QspObservablePropertyModel ref)
{
    m_propertyModelRefs.append(ref);
}

void oplink::ObservableModel::addProcessorModelRef(QspCommandProcessorModel ref)
{
    m_processorModelRefs.append(ref);
}

oplink::QspObservableBuilder oplink::ObservableModel::buildObservable(QspObservableBuilderArgs builderArgs)
{
    pfDebug3(logChannel()) << "->ObservableModel::buildObservable, Model [" << m_modelName << "]";

    QspObservableBuilder newObservable;

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

bool oplink::ObservableModel::buildProperties(QspObservableBuilder observableBuilder,
                                              QspObservableBuilderArgs builderArgs)
{
    bool ret{createMandatorProperties(observableBuilder)};

    if (ret)
    {
        ret = createProperties(observableBuilder);
        if (ret)
        {
            ret = setPropertyMandatoryValues(observableBuilder, builderArgs);
        }
    }

    return ret;
}

bool oplink::ObservableModel::buildProcessors(QspObservableBuilder observableBuilder,
                                              QspObservableBuilderArgs builderArgs)
{
    bool ret{true};
    Observable& parent{observableBuilder->toObservable()};
    QListIterator<QspCommandProcessorModel> it{m_processorModelRefs};

    while(it.hasNext() && ret)
    {
        QspCommandProcessorModel processorModel{it.next()};
        CommandProcessor* ptrProcessor{processorModel->createProcessor(parent, builderArgs)};

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

void oplink::ObservableModel::postBuild(QspObservableBuilder observableBuilder,
                                        QspObservableBuilderArgs builderArgs)
{
    Q_UNUSED(observableBuilder)
    Q_UNUSED(builderArgs)
    // No OP!
}

bool oplink::ObservableModel::createProperties(QspObservableBuilder observableBuilder)
{
    bool ret{true};
    Observable& parent{observableBuilder->toObservable()};
    QListIterator<QspObservablePropertyModel> it{m_propertyModelRefs};

    while(it.hasNext() && ret)
    {
        QspObservablePropertyModel propertyModel{it.next()};

        Property* ptrProperty{propertyModel->createProperty(parent)};

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

bool oplink::ObservableModel::createMandatorProperties(QspObservableBuilder observableBuilder)
{
    bool ret{true};
    oplink::Property *prop;

    // Name
    //-----
    prop = new oplink::Property{observableBuilder->toObservable(),
                                oplink::PropertyId::P_NAME,
                                QMetaType::QString};
    observableBuilder->addProperty(prop);

    // Model Name
    //-----------
    prop = new oplink::Property{observableBuilder->toObservable(),
                                oplink::PropertyId::P_MODEL,
                                QMetaType::QString};
    observableBuilder->addProperty(prop);

    // Localisation
    //-------------
    prop = new oplink::Property{observableBuilder->toObservable(),
                                oplink::PropertyId::P_LOCALISATION,
                                QMetaType::QString};
    observableBuilder->addProperty(prop);

    return ret;
}

bool oplink::ObservableModel::setPropertyMandatoryValues(QspObservableBuilder observableBuilder,
                                                         QspObservableBuilderArgs builderArgs)
{
    bool ret, ret1,ret2,ret3;

    ret1 = observableBuilder->setMandatoryPropertyValue(PropertyId::P_NAME, builderArgs->m_observableName);
    ret2 = observableBuilder->setMandatoryPropertyValue(PropertyId::P_MODEL, m_modelName);
    ret3 = observableBuilder->setMandatoryPropertyValue(PropertyId::P_LOCALISATION,builderArgs->m_observableLocalisation);
    ret = ret1 && ret2 && ret3;

    return ret;
}



