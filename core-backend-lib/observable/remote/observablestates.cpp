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


#include "observablestates.h"
#include "observable/property/property.h"

using namespace elekdom::oplink::core::remote;

ObservableStates::ObservableStates(QObject *parent):
    ObservableSubscriber{parent}
{

}

ObservableStates::~ObservableStates()
{

}

void ObservableStates::addMonitoredProperty(observable::QspProperty property)
{
    QString propertyName{property->name()};
    m_monitoredStates.insert(propertyName,property);
}

void ObservableStates::reportValidStates(const observable::ObservableName& observableName)
{
    QHash<observable::PropertyName,observable::QspProperty>::Iterator it{m_monitoredStates.begin()};
    observable::QspProperty curProperty;
    QString propertyName;

    while (it != m_monitoredStates.end())
    {
        curProperty = it.value();
        propertyName = it.key();

        if(curProperty->isValidValue())
        {
            QVariant val{curProperty->value()};

            // reports state
            emit stateChange(observableName,propertyName,val);
        }

        //next
        ++it;
    }
}

void ObservableStates::onStateChange(const observable::ObservableName& observableName,
                                     const observable::PropertyName& propertyName,
                                     QVariant propertyValue)
{
    if (m_monitoredStates.find(propertyName) != m_monitoredStates.end())
    {
        emit stateChange(observableName,propertyName,propertyValue);
    }
}

