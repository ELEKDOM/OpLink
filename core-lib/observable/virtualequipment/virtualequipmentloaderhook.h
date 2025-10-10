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


#ifndef VIRTUALEQUIPMENTLOADERHOOK_H
#define VIRTUALEQUIPMENTLOADERHOOK_H

#include "xmldom/browserhook.h"
#include "olcore-lib_export.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipment
{

class OLCORE_LIB_EXPORT VirtualEquipmentLoaderHook : public plugframe::core::xmldom::BrowserHook
{
public:
    ~VirtualEquipmentLoaderHook() override {}
};

}//namespace virtualequipment
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTLOADERHOOK_H
