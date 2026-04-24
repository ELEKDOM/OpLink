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

#include "remotemonitoredobservablegroup.h"
#include "remoteMonitoredobservable.h"

oplink::RemoteMonitoredObservableGroup::RemoteMonitoredObservableGroup(oplink::ObservableServiceInterface *oService,
                                                     QObject *parent):
    QObject{parent},
    m_observableService{oService}
{

}

oplink::RemoteMonitoredObservableGroup::~RemoteMonitoredObservableGroup()
{

}

void oplink::RemoteMonitoredObservableGroup::orderToObservable(const QString &order)
{
    if (m_observableService != nullptr)
    {
        m_observableService->submitOrder(order);
    }
}

void oplink::RemoteMonitoredObservableGroup::addRemoteMonitoredObservable(const QString& observableName,
                                                                    oplink::QspRemoteMonitoredObservable remoteMonitored)
{
    // add a new monitored observable
    m_remoteMonitoredObservables.insert(observableName,remoteMonitored);

    // connect to states change
    connect(remoteMonitored.data(),
            SIGNAL(stateChange(oplink::ObservableName,oplink::PropertyName,QVariant)),
            SLOT(onStateChange(oplink::ObservableName,oplink::PropertyName,QVariant)));
}

///
/// \brief RemoteMonitoredObservableGroup::subscribe
///        subscribes to state changes and reports initial values
void oplink::RemoteMonitoredObservableGroup::subscribe()
{
    QHash<oplink::ObservableName,oplink::QspRemoteMonitoredObservable>::Iterator it{m_remoteMonitoredObservables.begin()};
    oplink::QspRemoteMonitoredObservable curMonitored;
    QString observableName;

    if (m_observableService != nullptr)
    {
        while (it != m_remoteMonitoredObservables.end())
        {
            curMonitored = it.value();
            observableName = it.key();

            //subscribe
            m_observableService->subscribe(observableName,curMonitored.data(),true);// true to report initial values !

            //next
            ++it;
        }
    }
}

void oplink::RemoteMonitoredObservableGroup::unsubscribe()
{
    QHash<oplink::ObservableName,oplink::QspRemoteMonitoredObservable>::Iterator it{m_remoteMonitoredObservables.begin()};
    oplink::QspRemoteMonitoredObservable curMonitored;
    QString observableName;

    if (m_observableService != nullptr)
    {
        while (it != m_remoteMonitoredObservables.end())
        {
            curMonitored = it.value();
            observableName = it.key();

            //unsubscribe
            m_observableService->unsubscribe(observableName,curMonitored.data());

            //next
            ++it;
        }
    }

    m_remoteMonitoredObservables.clear();
}
