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

oplink::SupervisorObservable::SupervisorObservable()
{

}

oplink::SupervisorObservable::~SupervisorObservable()
{

}

void oplink::SupervisorObservable::addMonitoredObservableGroup(const QString &groupName,
                                                               oplink::QspMonitoredObservableGroup ptrGroup)
{
    if (!m_monitoredObservableGroups.contains(groupName))
    {
        m_monitoredObservableGroups.insert(groupName, ptrGroup);
    }
}

void oplink::SupervisorObservable::init(oplink::ObservableServiceInterface *observableService)
{
    specificInit(observableService);
}

QVariant oplink::SupervisorObservable::propertyValue(oplink::PropertyName propId)
{
    QVariant ret;
    QspProperty p{property(propId)};

    if (!p.isNull())
    {
        ret = p->value();
    }

    return ret;
}

void oplink::SupervisorObservable::initGroupAlgotithms(oplink::ObservableServiceInterface *observableService)
{
    QHash<QString,oplink::QspMonitoredObservableGroup>::const_iterator i = m_monitoredObservableGroups.constBegin();

    while (i != m_monitoredObservableGroups.constEnd())
    {
        oplink::QspMonitoredObservableGroup monitoredGroup{i.value()};

        monitoredGroup->initAlgorithm(observableService);
        ++i;
    }

}
