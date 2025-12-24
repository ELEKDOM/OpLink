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

#include "observablestatesgroup.h"
#include "observablestates.h"

oplink::ObservableStatesGroup::ObservableStatesGroup(oplink::ObservableServiceInterface *oService,
                                                     QObject *parent):
    QObject{parent},
    m_observableService{oService}
{

}

oplink::ObservableStatesGroup::~ObservableStatesGroup()
{

}

void oplink::ObservableStatesGroup::orderToObservable(const QString &order)
{
    if (m_observableService != nullptr)
    {
        m_observableService->submitOrder(order);
    }
}

void oplink::ObservableStatesGroup::addMonitoredObservable(const QString& observableName,
                                                           const QStringList& propertyNames,
                                                           oplink::QspObservableStates remoteMonitored)
{
    if (m_observableService != nullptr)
    {
        //  find the properties to monitor (monitored states)
        for (qsizetype i = 0; i < propertyNames.size(); ++i)
        {
            QString propertyName{propertyNames.at(i)};
            oplink::QspProperty property;

            property = m_observableService->property(observableName,propertyName);
            if (!property.isNull())
            {
                remoteMonitored->addMonitoredProperty(property);
            }
        }
    }

    // add a new monitored observable
    m_monitoredObservables.insert(observableName,remoteMonitored);

    // connect to states change
    connect(remoteMonitored.data(),
            SIGNAL(stateChange(oplink::ObservableName,oplink::PropertyName,QVariant)),
            SLOT(onStateChange(oplink::ObservableName,oplink::PropertyName,QVariant)));
}

///
/// \brief ObservableStatesGroup::subscribe
///        subscribes to state changes and reports initial values
void oplink::ObservableStatesGroup::subscribe()
{
    QHash<oplink::ObservableName,oplink::QspObservableStates>::Iterator it{m_monitoredObservables.begin()};
    oplink::QspObservableStates curMonitored;
    QString observableName;

    if (m_observableService != nullptr)
    {
        while (it != m_monitoredObservables.end())
        {
            curMonitored = it.value();
            observableName = it.key();

            //subscribe
            m_observableService->subscribe(observableName,curMonitored.data());

            //reports initial values
            curMonitored->reportValidStates(observableName);

            //next
            ++it;
        }
    }
}

void oplink::ObservableStatesGroup::unsubscribe()
{
    QHash<oplink::ObservableName,oplink::QspObservableStates>::Iterator it{m_monitoredObservables.begin()};
    oplink::QspObservableStates curMonitored;
    QString observableName;

    if (m_observableService != nullptr)
    {
        while (it != m_monitoredObservables.end())
        {
            curMonitored = it.value();
            observableName = it.key();

            //unsubscribe
            m_observableService->unsubscribe(observableName,curMonitored.data());

            //next
            ++it;
        }
    }

    m_monitoredObservables.clear();
}
