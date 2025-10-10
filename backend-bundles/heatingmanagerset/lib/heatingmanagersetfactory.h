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


#ifndef HEATINGMANAGERSETFACTORY_H
#define HEATINGMANAGERSETFACTORY_H

#include "abstract_virtualequipementset/virtualequipmentsetfactory.h"

namespace elekdom
{
namespace oplink
{
namespace heatingmanagerset
{
namespace factory
{

class HeatingManagerSetFactory : public core::virtualequipmentset::factory::VirtualEquipmentSetFactory
{
public:
    HeatingManagerSetFactory();
    virtual ~HeatingManagerSetFactory();

protected:
    core::virtualequipment::VirtualEquipmentLoader *createVirtualEquipmentLoader(core::virtualequipmentset::bundle::VirtualEquipmentSet *veSet) override;
    core::virtualequipment::VirtualEquipmentConfDocument *createVirtualEquipmentConfDocument(core::virtualequipment::VirtualEquipmentLoaderHook& hook) override;
};

}//namespace factory
}//namespace heatingmanagerset
}//namespace oplink
}//namespace elekdom

#endif // HEATINGMANAGERSETFACTORY_H
