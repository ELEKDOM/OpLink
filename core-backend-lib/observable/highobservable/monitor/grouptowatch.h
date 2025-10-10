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


#ifndef GROUPTOWATCH_H
#define GROUPTOWATCH_H

#include <QHash>
#include <QString>
#include "olcore-backend-lib_export.h"
#include "service-int/observableserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{
namespace monitoring
{

class OLCORE_BACKEND_LIB_EXPORT GroupToWatch
{
public:
    GroupToWatch(QspMonitoredGroupAlgorithm algo);
    virtual ~GroupToWatch();

public:
    void groupName(const QString& name) {m_groupName = name;}
    const QString& groupName() {return m_groupName;}
    void addCategory(const QString& categoryName);
    bool isCategoryEmpty(const QString& categoryName);
    void addMonitoredState(const QString& categoryName, QspMonitoredState monitoredState);
    QspMonitoredStateList category(const QString& categoryName);
    void initAlgorithm(engine::service::ObservableServiceInterface *observableService);
    GroupToWatchAlgorithm* algorithm();
    QString reverseLookUp(const QString& reverseInput);
    bool allTrue(const QString& categoryName);

private:
    QHash<QString, QspMonitoredStateList> m_categories;
    QHash<QString, QString>               m_reversLookUp; // observablename + property name => category name
    QspMonitoredGroupAlgorithm            m_algorithm;
    QString                               m_groupName;
};

}//namespace monitoring
}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // GROUPTOWATCH_H
