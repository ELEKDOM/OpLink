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


#ifndef OBSERVABLECLASSNAMES_H
#define OBSERVABLECLASSNAMES_H

#include "olcore-backend-lib_export.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class OLCORE_BACKEND_LIB_EXPORT ObservableClassNames
{
public:
    static const ObservableType ACTUATOR_CLASS;
    static const ObservableType SENSOR_CLASS;
    static const ObservableType LOAD_CLASS;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLECLASSNAMES_H
