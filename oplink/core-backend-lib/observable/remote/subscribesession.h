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

#ifndef SUBSCRIBESESSION_H
#define SUBSCRIBESESSION_H

#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include "observable/remote/observablestatesgroup.h"
#include "observable/remote/sessionconfdocument.h"
#include "observable/remote/sessionconfloader.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT SubscribeSession : public ObservableStatesGroup
{
    Q_OBJECT

public:
    SubscribeSession(quint32 sessionId,
                     const QString& filename,
                     ObservableServiceInterface *oService,
                     QObject *parent = nullptr);

    ~SubscribeSession() override;

public:
    bool open(qint16& confId);
    void close();
    QString confContent();
    void submitOrder(const QString &order);
    void addRemoteMonitoredObservable(const QString& observableName,
                                      const QStringList& propertyNames,
                                      QspObservableStates remoteMonitored);
    void enableMonitoring();

signals:
    void newState(quint32 sessionId,
                  oplink::ObservableName observableName,
                  oplink::PropertyName propertyName,
                  QVariant propertyValue);
protected:
    void onStateChange(ObservableName observableName,
                       PropertyName propertyName,
                       QVariant propertyValue) override;
private:
    quint32             m_sessionId;
    QString             xmlFileName;
    SessionConfDocument m_domDoc;
    SessionConfLoader   m_confLoader;
};
using QspSubscribeSession = QSharedPointer<SubscribeSession>;
}//namespace oplink
#endif // SUBSCRIBESESSION_H
