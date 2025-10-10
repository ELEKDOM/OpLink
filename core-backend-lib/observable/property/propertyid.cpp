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


#include "propertyid.h"

using namespace elekdom::oplink::core::observable;

const PropertyName PropertyId::P_NAME {"p_name"};
const PropertyName PropertyId::P_MODEL {"p_model"};
const PropertyName PropertyId::P_LOCALISATION {"p_localisation"};
const PropertyName PropertyId::P_CONF {"p_conf"};
const PropertyName PropertyId::P_MODE {"p_mode"};
const PropertyName PropertyId::P_ORDER{"p_order"};
const PropertyName PropertyId::P_DEROGATED{"p_derogated"};
const PropertyName PropertyId::P_DEROGATED_ORDER{"p_derogated_order"};
const PropertyName PropertyId::P_WCLOSED{"p_wclosed"};
const PropertyName PropertyId::P_TEMPERATURE{"p_temperature"};

QString PropertyId::groupPropertyName(const QString &groupName, const PropertyName &propertyName)
{
    return (groupName+ '_' + propertyName);
}
