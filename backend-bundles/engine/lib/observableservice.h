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


#ifndef OBSERVABLESERVICE_H
#define OBSERVABLESERVICE_H

#include <QHash>
#include "olcore-backend-lib_forward.h"
#include "service/serviceimplementation.h"
#include "observable/observablenames.h"
#include "command/command-names.h"

namespace elekdom
{
namespace oplink
{
namespace engine
{
namespace service
{
using Hash_RegisteredObs = QHash<core::observable::ObservableName, core::observable::QspObservable>;

class ObservableService : public plugframe::core::service::ServiceImplementation
{
public:
    ObservableService(plugframe::core::bundle::BundleImplementation *implementation);
    ~ObservableService() override;

public:
    bool submitOrder(core::command::StrOrder command);
    bool subscribe(core::observable::ObservableName observableName,
                   core::observable::ObservableSubscriber *subscriber);
    bool unsubscribe(core::observable::ObservableName observableName,
                     core::observable::ObservableSubscriber *subscriber);
    bool propertyValue(core::observable::ObservableName observableName,
                       core::observable::PropertyName propertyName,
                       QVariant& value);
    core::observable::QspProperty property(core::observable::ObservableName observableName,
                                           core::observable::PropertyName propertyName);

public:
    void registerObservables(const core::observable::QspObservableBuildersContainer& loadedObservables);

protected:
    QString serviceName() override;

private:
    core::observable::QspObservable lookupObservable(const core::observable::ObservableName& name);

private:
    Hash_RegisteredObs m_registeredObservables;

};

}//namespace service
}//namespace engine
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLESERVICE_H
