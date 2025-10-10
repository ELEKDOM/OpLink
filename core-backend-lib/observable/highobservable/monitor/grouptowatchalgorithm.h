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

#include "observable/observable/observablesubscriber.h"
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

class OLCORE_BACKEND_LIB_EXPORT GroupToWatchAlgorithm : public ObservableSubscriber
{
public:
    GroupToWatchAlgorithm(SupervisorObservable& manager, QObject *parent = nullptr);
    ~GroupToWatchAlgorithm() override;

public:
    virtual void initAlgorithm(engine::service::ObservableServiceInterface *observableService);
    void group(GroupToWatch *group) {m_group = group;}

protected:
    virtual void initAlgo() = 0;

protected:
    SupervisorObservable& manager() {return m_manager;}
    GroupToWatch *group() {return m_group;}
    void subscribeToCategory(const QString& category,
                             core::observable::monitoring::GroupToWatch *myRoom,
                             engine::service::ObservableServiceInterface *observableService);
    engine::service::ObservableServiceInterface *observableService() {return m_observableService;}

private:
    SupervisorObservable& m_manager;
    GroupToWatch *m_group;
    engine::service::ObservableServiceInterface *m_observableService;
};

}//namespace monitoring
}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // GROUPTOWATCHALGORITHM_H
