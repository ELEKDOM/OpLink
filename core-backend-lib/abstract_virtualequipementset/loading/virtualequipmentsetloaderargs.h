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


#ifndef VIRTUALEQUIPMENTSETLOADERARGS_H
#define VIRTUALEQUIPMENTSETLOADERARGS_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "worker/workerargs.h"

using namespace elekdom::plugframe::core;

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipmentset
{

class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetLoaderArgs : public worker::WorkerArgs
{
public:
    VirtualEquipmentSetLoaderArgs(virtualequipment::QspVirtualEquipmentLoader veLoader);
    ~VirtualEquipmentSetLoaderArgs();

public:
    virtualequipment::QspVirtualEquipmentLoader m_veLoader;
};

}//namespace virtualequipmentset
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTSETLOADERARGS_H
