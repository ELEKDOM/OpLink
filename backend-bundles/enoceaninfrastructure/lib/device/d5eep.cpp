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

#include "d5eep.h"
#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"

D5Eep::D5Eep(const oplink::DeviceId& id,
             oplink::DeviceHook& deviceHook,
             EepTelegramFormat *msgFormat):
    EnoceanEquipmentProfile{id, deviceHook, msgFormat}
{

}

D5Eep::~D5Eep()
{

}

void D5Eep::recoverState()
{
    //NO OP!
}

bool D5Eep::processTelegram()
{
    bool ret;

    ret = msgFormat()->getRorg() == EepTelegramFormat::RORG_D5;
    return ret;
}
