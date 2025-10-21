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

#ifndef OBSERVABLESTATESGROUP_H
#define OBSERVABLESTATESGROUP_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include "service-int/observableserviceinterface.h"
#include "observable/observablenames.h"
#include "observable/remote/observablestates.h"

namespace oplink
{
class ObservableStatesGroup : public QObject
{
    Q_OBJECT

public:
    explicit ObservableStatesGroup(ObservableServiceInterface *oService,
                                   QObject *parent = nullptr);
    ~ObservableStatesGroup() override;

public slots:
    virtual void onStateChange(ObservableName observableName,
                               PropertyName propertyName,
                               QVariant propertyValue) = 0;

protected:
    void orderToObservable(const QString &order);
    void addMonitoredObservable(const QString& observableName,
                                const QStringList& propertyNames,
                                QspObservableStates remoteMonitored);
    void subscribe();
    void unsubscribe();

private:
    ObservableServiceInterface               *m_observableService;
    QHash<ObservableName,QspObservableStates> m_monitoredObservables;
};
}//namespace oplink
#endif // OBSERVABLESTATESGROUP_H
