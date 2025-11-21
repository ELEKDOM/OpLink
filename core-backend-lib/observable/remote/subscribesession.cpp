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

#include <QVariant>
#include "subscribesession.h"

oplink::SubscribeSession::SubscribeSession(quint32 sessionId,
                                           const QString &filename,
                                           oplink::ObservableServiceInterface *oService,
                                           QObject *parent):
    oplink::ObservableStatesGroup{oService,parent},
    m_sessionId{sessionId},
    xmlFileName{filename},
    m_domDoc{m_confLoader},
    m_confLoader{*this}
{

}

oplink::SubscribeSession::~SubscribeSession()
{

}

bool oplink::SubscribeSession::open(qint16 &confId)
{
    bool ret{false};

    m_domDoc.load(xmlFileName); // first load xml dom structure

    if (m_domDoc.fileLoaded())
    {
        confId = m_domDoc.confId();
        ret = m_domDoc.browse();
    }

    return ret;
}

void oplink::SubscribeSession::close()
{
    unsubscribe();
}

QString oplink::SubscribeSession::confContent()
{
    return m_domDoc.toString();
}

void oplink::SubscribeSession::submitOrder(const QString &order)
{
    orderToObservable(order);
}

void oplink::SubscribeSession::addRemoteMonitoredObservable(const QString& observableName,
                                                            const QStringList& propertyNames,
                                                            oplink::QspObservableStates  remoteMonitored)
{
    addMonitoredObservable(observableName,propertyNames,remoteMonitored);
}

void oplink::SubscribeSession::enableMonitoring()
{
    subscribe();
}

void oplink::SubscribeSession::onStateChange(oplink::ObservableName observableName,
                                             oplink::PropertyName propertyName,
                                             QVariant propertyValue)
{
    emit newState(m_sessionId,observableName,propertyName,propertyValue);
}
