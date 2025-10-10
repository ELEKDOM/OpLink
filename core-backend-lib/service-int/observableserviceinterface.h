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


#ifndef OBSERVABLESERVICEINTERFACE_H
#define OBSERVABLESERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "olcore-backend-lib_forward.h"
#include "command/command-names.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace engine
{
namespace service
{

class ObservableServiceInterface : public plugframe::core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("ObservableServiceInterface");}

public:
    virtual ~ObservableServiceInterface() {}

public: // service interface definition = 0
    virtual bool submitOrder(core::command::StrOrder command) = 0;
    virtual bool subscribe(core::observable::ObservableName observableName,
                           core::observable::ObservableSubscriber *subscriber) = 0;
    virtual bool unsubscribe(core::observable::ObservableName observableName,
                             core::observable::ObservableSubscriber *subscriber) = 0;
    virtual bool propertyValue(core::observable::ObservableName observableName,
                               core::observable::PropertyName propertyName,
                               QVariant& value) = 0;
    virtual core::observable::QspProperty property(core::observable::ObservableName observableName,
                                                   core::observable::PropertyName propertyName) = 0;
};

}//namespace service
}//namespace engine
}//namespace oplink
}//namespace elekdom

#define OlObservableService_iid "elekdom.oplink.engine.service.ObservableService"
Q_DECLARE_INTERFACE(elekdom::oplink::engine::service::ObservableServiceInterface, OlObservableService_iid)

#endif // OBSERVABLESERVICEINTERFACE_H
