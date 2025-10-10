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


#ifndef CORELIBCOMMANDNAMES_H
#define CORELIBCOMMANDNAMES_H

#include <QString>
#include "olcore-lib_export.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace command
{

using StrOrder = QString; // <command name>;<observable name>;[<property name>];[value]
using CommandName = QString;
using CommandArg = QString;

class OLCORE_LIB_EXPORT CommandNames
{
public:
    static const oplink::core::command::CommandName SYNCHRONIZE;
    static const oplink::core::command::CommandName SET;
    static const oplink::core::command::CommandName ENERGY;
    static const oplink::core::command::CommandName POWER;
};

class OLCORE_LIB_EXPORT CommandArgs
{
public:
    static const oplink::core::command::CommandArg ON;
    static const oplink::core::command::CommandArg OFF;
    static const oplink::core::command::CommandArg COMFORT;
    static const oplink::core::command::CommandArg COMFORT_1;
    static const oplink::core::command::CommandArg COMFORT_2;
    static const oplink::core::command::CommandArg ECO;
    static const oplink::core::command::CommandArg NOFROST;

};

}//namespace command
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // CORELIBCOMMANDNAMES_H
