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

#ifndef GROUPTOWATCHALGORITHM_H
#define GROUPTOWATCHALGORITHM_H

#include <QSharedPointer>
#include "observable/observable/observablesubscriber.h"
#include "service-int/observableserviceinterface.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT GroupToWatchAlgorithm : public oplink::ObservableSubscriber
{
public:
    GroupToWatchAlgorithm(SupervisorObservable& manager, QObject *parent = nullptr);
    ~GroupToWatchAlgorithm() override;

public:
    virtual void initAlgorithm(ObservableServiceInterface *observableService);
    void group(GroupToWatch *group) {m_group = group;}

protected:
    virtual void initAlgo() = 0;

protected:
    SupervisorObservable& manager() {return m_manager;}
    GroupToWatch *group() {return m_group;}
    void subscribeToCategory(const QString& category,
                             GroupToWatch *myRoom,
                             ObservableServiceInterface *observableService);
    ObservableServiceInterface *observableService() {return m_observableService;}

private:
    SupervisorObservable&       m_manager;
    GroupToWatch               *m_group;
    ObservableServiceInterface *m_observableService;
};
using QspMonitoredGroupAlgorithm = QSharedPointer<GroupToWatchAlgorithm>;
}//namespace oplink
#endif // GROUPTOWATCHALGORITHM_H
