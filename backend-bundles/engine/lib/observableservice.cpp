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


#include "observableservice.h"
#include "serverengine.h"
#include "service-int/observableserviceinterface.h"
#include "command/command.h"
#include "observable/property/property.h"
#include "observable/observable/observable.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "logger/pflog.h"

using namespace elekdom::oplink::engine::service;
using namespace elekdom::oplink::core;

ObservableService::ObservableService(elekdom::plugframe::core::bundle::BundleImplementation *implementation):
    plugframe::core::service::ServiceImplementation{implementation}
{

}

ObservableService::~ObservableService()
{

}

bool ObservableService::submitOrder(core::command::StrOrder command)
{
    QMutexLocker                 lock(&m_mtx);
    bool                         ret{false};
    command::QspCommand       cmd{new command::Command{command}};
    observable::QspObservable observable{lookupObservable(cmd->observable())};

    if (!observable.isNull())
    {
        ret = true;
        observable->process(cmd);
    }

    return ret;
}

bool ObservableService::subscribe(core::observable::ObservableName observableName,
                                           core::observable::ObservableSubscriber *subscriber)
{
    QMutexLocker                 lock(&m_mtx);
    bool                         ret{false};
    observable::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        ret = observable->subscribe(subscriber);
    }

    return ret;
}

bool ObservableService::unsubscribe(core::observable::ObservableName observableName,
                                             core::observable::ObservableSubscriber *subscriber)
{
    QMutexLocker                 lock(&m_mtx);
    bool                         ret{false};
    observable::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        ret = observable->unsubscribe(subscriber);
    }

    return ret;
}

bool ObservableService::propertyValue(core::observable::ObservableName observableName,
                                      core::observable::PropertyName propertyName,
                                      QVariant& value)
{
    QMutexLocker lock(&m_mtx);
    bool ret{false};
    observable::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        observable::QspProperty property{observable->property(propertyName)};
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

observable::QspProperty ObservableService::property(core::observable::ObservableName observableName, core::observable::PropertyName propertyName)
{
    QMutexLocker lock(&m_mtx);
    observable::QspProperty ret;
    observable::QspObservable observable{lookupObservable(observableName)};

    if (!observable.isNull())
    {
        ret = observable->property(propertyName);
    }

    return ret;
}

void ObservableService::registerObservables(const core::observable::QspObservableBuildersContainer &loadedObservables)
{
    QMutexLocker lock(&m_mtx);

    for(observable::ObservableBuildersContainer::ConstIt it = loadedObservables->begin(); it != loadedObservables->end(); it++)
    {
        observable::QspObservable obs{(*it).dynamicCast<observable::Observable>()};
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
    return service::ObservableServiceInterface::serviceName();
}

observable::QspObservable ObservableService::lookupObservable(const core::observable::ObservableName &name)
{
    return m_registeredObservables.value(name);
}


