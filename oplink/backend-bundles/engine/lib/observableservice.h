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
#include <QSharedPointer>
#include "service/serviceimplementation.h"
#include "observable/observable/observable.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "command/command-names.h"

using Hash_RegisteredObs = QHash<oplink::ObservableName, oplink::QspObservable>;

class ObservableService : public plugframe::ServiceImplementation
{
public:
    ObservableService(plugframe::BundleImplementation *implementation);
    ~ObservableService() override;

public:
    bool submitOrder(oplink::StrOrder command);
    bool subscribe(oplink::ObservableName observableName,
                   oplink::ObservableSubscriber *subscriber);
    bool unsubscribe(oplink::ObservableName observableName,
                     oplink::ObservableSubscriber *subscriber);
    bool propertyValue(oplink::ObservableName observableName,
                       oplink::PropertyName propertyName,
                       QVariant& value);
    oplink::QspProperty property(oplink::ObservableName observableName,
                                 oplink::PropertyName propertyName);

public:
    void registerObservables(const oplink::QspObservableBuildersContainer& loadedObservables);

protected:
    QString serviceName() override;

private:
    oplink::QspObservable lookupObservable(const oplink::ObservableName& name);

private:
    Hash_RegisteredObs m_registeredObservables;
};
using QspObservableService = QSharedPointer<ObservableService>;
#endif // OBSERVABLESERVICE_H
