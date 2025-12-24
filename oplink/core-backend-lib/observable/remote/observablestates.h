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

#ifndef OBSERVABLESTATES_H
#define OBSERVABLESTATES_H

#include <QSharedPointer>
#include <QHash>
#include "observable/observable/observablesubscriber.h"
#include "observable/property/property.h"
#include "observable/observablenames.h"

namespace oplink
{
class ObservableStates : public ObservableSubscriber
{
    Q_OBJECT

public:
    explicit ObservableStates(QObject *parent = nullptr);
    ~ObservableStates() override;

public:
    void addMonitoredProperty(QspProperty property);
    void reportValidStates(const ObservableName& observableName);

signals:
    void stateChange(oplink::ObservableName observableName,
                     oplink::PropertyName propertyName,
                     QVariant propertyValue);

protected:
    void onStateChange(ObservableName observableName,
                       PropertyName propertyName,
                       QVariant propertyValue) override;
private:
    QHash<PropertyName,QspProperty> m_monitoredStates;
};
using QspObservableStates = QSharedPointer<ObservableStates>;
}//namespace oplink
#endif // OBSERVABLESTATES_H
