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

#ifndef PROPERTYCLASSNAMES_H
#define PROPERTYCLASSNAMES_H

#include "olcore-backend-lib_export.h"
#include "observable/observablenames.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT PropertyClassNames
{
public:
    static const PropertyType PROPERTY_CLASS;
    static const PropertyType LOAD_PROPERTY_CLASS;
    static const PropertyType ACTUATOR_PROPERTY_CLASS;
    static const PropertyType SENSOR_PROPERTY_CLASS;
};
}//namespace oplink
#endif // PROPERTYCLASSNAMES_H
