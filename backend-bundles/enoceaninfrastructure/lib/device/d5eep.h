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


#ifndef D5EEP_H
#define D5EEP_H

#include "abstract_infrastructure/infrastructure-names.h"
#include "abstract_infrastructure/device/devicehook.h"
#include "enoceanequipmentprofile.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class D5Eep : public EnoceanEquipmentProfile
{
public:
    D5Eep(const core::infrastructure::DeviceId& id,
          core::infrastructure::DeviceHook& deviceHook,
          EepTelegramFormat *msgFormat);
    ~D5Eep() override;

protected:
    void recoverState() override;
    bool processTelegram() override;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // D5EEP_H
