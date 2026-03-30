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

#include "bundle/bundleimplementation.h"
#include "observableservice.h"
#include "service-int/observableserviceinterface.h"
#include "command/command.h"
#include "observable/property/property.h"
#include "observable/observable/observable.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "logger/pflog.h"

ObservableService::ObservableService(plugframe::BundleImplementation *implementation):
    plugframe::ServiceImplementation{implementation}
{

}

ObservableService::~ObservableService()
{

}

bool ObservableService::submitOrder(oplink::StrOrder command)
{ 
    bool                  ret{false};
    oplink::QspCommand    cmd{new oplink::Command{command}};
    oplink::QspObservable observable{lookupObservable(cmd->observable())};

    if (!observable.isNull())
    {
        ret = true;
        observable->process(cmd);
    }
    else
    {
        pfWarning1(implementation()->logChannel()) << QObject::tr("Adressage d'une commande impossible car [%1] n'est pas un nom d'observable enregistré!").arg(cmd->observable());
    }

    return ret;
}

bool ObservableService::subscribe(oplink::ObservableName observableName,
                                  oplink::ObservableSubscriber *subscriber)
{
    QMutexLocker          lock(&m_mtx);
    bool                  ret{false};
    oplink::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        ret = observable->subscribe(subscriber);
    }

    return ret;
}

bool ObservableService::unsubscribe(oplink::ObservableName observableName,
                                    oplink::ObservableSubscriber *subscriber)
{
    QMutexLocker          lock(&m_mtx);
    bool                  ret{false};
    oplink::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        ret = observable->unsubscribe(subscriber);
    }

    return ret;
}

bool ObservableService::propertyValue(oplink::ObservableName observableName,
                                      oplink::PropertyName propertyName,
                                      QVariant& value)
{
    QMutexLocker lock(&m_mtx);
    bool ret{false};
    oplink::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        oplink::QspProperty property{observable->property(propertyName)};
        if (!property.isNull())
        {
            ret = property->isValidValue();
            if (ret)
            {
                value = property->value();
            }
        }
    }

    return ret;
}

oplink::QspProperty ObservableService::property(oplink::ObservableName observableName,
                                                oplink::PropertyName propertyName)
{
    QMutexLocker          lock(&m_mtx);
    oplink::QspProperty   ret;
    oplink::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        ret = observable->property(propertyName);
    }

    return ret;
}

void ObservableService::registerObservables(const oplink::QspObservableBuildersContainer& loadedObservables)
{
    QMutexLocker lock(&m_mtx);

    for(oplink::ObservableBuildersContainer::ConstIt it = loadedObservables->begin(); it != loadedObservables->end(); it++)
    {
        oplink::QspObservable obs{(*it).dynamicCast<oplink::Observable>()};
        if (!m_registeredObservables.contains(obs->name()))
        {
            pfInfo1(implementation()->logChannel()) << QObject::tr("%1 enregistré pour suivi").arg(obs->name());
            m_registeredObservables.insert(obs->name(), obs);
        }
        else
        {
            pfWarning1(implementation()->logChannel()) << QObject::tr("%1 déjà enregistré!").arg(obs->name());
        }
    }
}

QString ObservableService::serviceName()
{
    return oplink::ObservableServiceInterface::serviceName();
}

oplink::QspObservable ObservableService::lookupObservable(const oplink::ObservableName& name)
{
    return m_registeredObservables.value(name);
}


