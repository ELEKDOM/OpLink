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
#include "service-int/observableserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class OLCORE_BACKEND_LIB_EXPORT SupervisorObservable : public HighObservable
{
protected:
    using HashGroup = QHash<QString,monitoring::QspMonitoredObservableGroup>;

public:
    SupervisorObservable();
    ~SupervisorObservable() override;

public:
    void addMonitoredObservableGroup(const QString& groupName,
                                     monitoring::QspMonitoredObservableGroup ptrGroup);
    void init(engine::service::ObservableServiceInterface *observableService);
    QVariant propertyValue(PropertyName propId);

protected:
    virtual void specificInit(engine::service::ObservableServiceInterface *observableService) = 0;
    void initGroupAlgotithms(engine::service::ObservableServiceInterface *observableService);
    const HashGroup& groups() {return m_monitoredObservableGroups;}

private:
    QHash<QString,monitoring::QspMonitoredObservableGroup> m_monitoredObservableGroups;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // SUPERVISOROBSERVABLE_H
