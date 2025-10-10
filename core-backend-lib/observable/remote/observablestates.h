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

#include <QHash>
#include "observable/observable/observablesubscriber.h"
#include "observable/observablenames.h"
#include "olcore-backend-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace remote
{

class ObservableStates : public observable::ObservableSubscriber
{
    Q_OBJECT

public:
    explicit ObservableStates(QObject *parent = nullptr);
    ~ObservableStates() override;

public:
    void addMonitoredProperty(observable::QspProperty property);
    void reportValidStates(const observable::ObservableName& observableName);

signals:
    void stateChange(const observable::ObservableName& observableName,
                     const observable::PropertyName& propertyName,
                     QVariant propertyValue);

protected:
    void onStateChange(const observable::ObservableName& observableName,
                       const observable::PropertyName& propertyName,
                       QVariant propertyValue) override;
private:
    QHash<observable::PropertyName,observable::QspProperty> m_monitoredStates;
};

}//namespace remote
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLESTATES_H
