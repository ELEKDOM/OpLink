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
#include "observable/observable/highobservable/highobservable.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/grouptowatch.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT SupervisorObservable : public HighObservable
{
protected:
    using HashGroup = QHash<QString,QspGroupToWatch>;

public:
    SupervisorObservable(const plugframe::QspScheduler& scheduler);
    ~SupervisorObservable() override;

public:
    void addMonitoredObservableGroup(const QString& groupName,
                                     QspGroupToWatch ptrGroup);

protected:
    void subscribeToMonitoredObservables();
    void unsubscribeToMonitoredObservables();
    const HashGroup& groups() {return m_monitoredObservableGroups;}
    QspGroupToWatch group(const QString& groupName) {return m_monitoredObservableGroups.value(groupName);}

private:
    HashGroup m_monitoredObservableGroups;
};
}//namespace oplink
#endif // SUPERVISOROBSERVABLE_H
