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

#include "statetowatch.h"
#include "observable/observable/observable.h"
#include "observable/property/property.h"

oplink::StateToWatch::StateToWatch(oplink::QspProperty& property):
    m_property{property}
{

}

const QString& oplink::StateToWatch::observableName()
{
    return m_property->observable().name();
}

const QString& oplink::StateToWatch::propertyName()
{
    return m_property->name();
}

QVariant oplink::StateToWatch::value()
{
    return m_property->value();
}

bool oplink::StateToWatch::isValidValue()
{
    return m_property->isValidValue();
}
