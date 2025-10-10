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


#ifndef ACTUATOROUTPUT_H
#define ACTUATOROUTPUT_H

#include "olcore-backend-lib_export.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{

class OLCORE_BACKEND_LIB_EXPORT ActuatorOutput
{
public:
    ActuatorOutput(const observable::PropertyName& actuatorPropertyName,
                      const observable::ObservableName& loadName,
                      const observable::PropertyName& loadPropertyName);

public:
    const observable::PropertyName& actuatorPropertyName() {return m_actuatorPropertyName;}
    const observable::ObservableName& loadName() {return m_loadName;}
    const observable::PropertyName& loadPropertyName() {return m_loadPropertyName;}

public:
    observable::PropertyName   m_actuatorPropertyName;
    observable::ObservableName m_loadName;
    observable::PropertyName   m_loadPropertyName;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // ACTUATOROUTPUT_H
