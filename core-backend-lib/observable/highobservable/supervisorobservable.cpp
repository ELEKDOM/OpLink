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


#include "supervisorobservable.h"
#include "observable/property/property.h"
#include "observable/highobservable/monitor/grouptowatch.h"

using namespace elekdom::oplink::core::observable;

SupervisorObservable::SupervisorObservable()
{

}

SupervisorObservable::~SupervisorObservable()
{

}

void SupervisorObservable::addMonitoredObservableGroup(const QString &groupName,
                                                       monitoring::QspMonitoredObservableGroup ptrGroup)
{
    if (!m_monitoredObservableGroups.contains(groupName))
    {
        m_monitoredObservableGroups.insert(groupName, ptrGroup);
    }
}

void SupervisorObservable::init(engine::service::ObservableServiceInterface *observableService)
{
    specificInit(observableService);
}

QVariant SupervisorObservable::propertyValue(PropertyName propId)
{
    QVariant ret;
    QspProperty p{property(propId)};

    if (!p.isNull())
    {
        ret = p->value();
    }

    return ret;
}

void SupervisorObservable::initGroupAlgotithms(engine::service::ObservableServiceInterface *observableService)
{
    QHash<QString,monitoring::QspMonitoredObservableGroup>::const_iterator i = m_monitoredObservableGroups.constBegin();

    while (i != m_monitoredObservableGroups.constEnd())
    {
        monitoring::QspMonitoredObservableGroup monitoredGroup{i.value()};

        monitoredGroup->initAlgorithm(observableService);
        ++i;
    }

}
