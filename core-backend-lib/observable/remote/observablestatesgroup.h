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
#include "olcore-backend-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace remote
{

class ObservableStatesGroup : public QObject
{
    Q_OBJECT

public:
    explicit ObservableStatesGroup(engine::service::ObservableServiceInterface *oService,
                                   QObject *parent = nullptr);
    ~ObservableStatesGroup() override;

public slots:
    virtual void onStateChange(const observable::ObservableName& observableName,
                               const observable::PropertyName& propertyName,
                               QVariant propertyValue) = 0;

protected:
    void orderToObservable(const QString &order);
    void addMonitoredObservable(const QString& observableName,
                                const QStringList& propertyNames,
                                core::remote::QspObservableStates remoteMonitored);
    void subscribe();
    void unsubscribe();

private:
    engine::service::ObservableServiceInterface                        *m_observableService;
    QHash<observable::ObservableName,core::remote::QspObservableStates> m_monitoredObservables;
};

}//namespace remote
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLESTATESGROUP_H
