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


#include "property.h"
#include "observable/observablelogchannel.h"
#include "observable/observable/observable.h"

using namespace elekdom::oplink::core::observable;

Property::Property(Observable &observable,
                         const PropertyName &propertyName,
                         QVariant::Type valueType) :
    plugframe::core::logger::Loggable{s_ObservableLogChannel},
    m_observable{observable},
    m_name{propertyName},
    m_value{valueType},
    m_validValue{false}
{

}

Property::~Property()
{

}

void Property::value(const QVariant &val)
{
    m_value = val;
    m_validValue = true;
}

void Property::changeValue(const QVariant &val)
{
    if (!m_validValue || (val != value()))
    {
        value(val);
        m_observable.notifyPropertyValueChange(*this);
    }
}
