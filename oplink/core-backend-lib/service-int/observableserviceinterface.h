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
#include "command/command-names.h"
#include "observable/observablenames.h"
#include "observable/property/property.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class ObservableServiceInterface : public plugframe::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("ObservableServiceInterface");}

public:
    virtual ~ObservableServiceInterface() {}

public: // service interface definition = 0
    virtual bool submitOrder(oplink::StrOrder command) = 0;
    virtual bool subscribe(oplink::ObservableName observableName,
                           oplink::ObservableSubscriber *subscriber,
                           bool reportInitialValues = false) = 0;
    virtual bool unsubscribe(oplink::ObservableName observableName,
                             oplink::ObservableSubscriber *subscriber) = 0;
    virtual bool propertyValue(oplink::ObservableName observableName,
                               oplink::PropertyName propertyName,
                               QVariant& value) = 0;
    virtual oplink::QspProperty property(oplink::ObservableName observableName,
                                         oplink::PropertyName propertyName) = 0;
};
}//namespace oplink

#define OlObservableService_iid "oplink.ObservableServiceInterface"
Q_DECLARE_INTERFACE(oplink::ObservableServiceInterface, OlObservableService_iid)

#endif // OBSERVABLESERVICEINTERFACE_H
