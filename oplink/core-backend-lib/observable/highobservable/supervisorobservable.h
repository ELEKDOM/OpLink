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

#ifndef SUPERVISOROBSERVABLE_H
#define SUPERVISOROBSERVABLE_H

#include <QString>
#include <QStringList>
#include <QHash>
#include "observable/highobservable/highobservable.h"
#include "observable/highobservable/monitor/grouptowatch.h"
#include "service-int/observableserviceinterface.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT SupervisorObservable : public HighObservable
{
protected:
    using HashGroup = QHash<QString,QspMonitoredObservableGroup>;

public:
    SupervisorObservable();
    ~SupervisorObservable() override;

public:
    void addMonitoredObservableGroup(const QString& groupName,
                                     QspMonitoredObservableGroup ptrGroup);
    void init(ObservableServiceInterface *observableService);
    QVariant propertyValue(PropertyName propId);

protected:
    virtual void specificInit(ObservableServiceInterface *observableService) = 0;
    void initGroupAlgotithms(ObservableServiceInterface *observableService);
    const HashGroup& groups() {return m_monitoredObservableGroups;}

private:
    HashGroup m_monitoredObservableGroups;
};
}//namespace oplink
#endif // SUPERVISOROBSERVABLE_H
