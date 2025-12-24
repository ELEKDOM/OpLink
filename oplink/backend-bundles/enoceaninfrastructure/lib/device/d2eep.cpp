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

#include "d2eep.h"
#include "packet/format/sentformat/eepcommandformat/D2/d201cmd3format.h"

D2Eep::D2Eep(const oplink::DeviceId &id,
             oplink::DeviceHook& deviceHook,
             EepTelegramFormat *msgFormat):
    EnoceanEquipmentProfile{id, deviceHook, msgFormat}
{

}

D2Eep::~D2Eep()
{

}

void D2Eep::recoverState()
{
    // To recover D2 EnOcean Equipment State, a command "Status Query" must be send to device
    QspD201Cmd3Format cmdFormat{new D201Cmd3Format};
    qint32 destinationId{id().toInt(nullptr, 16)};

    cmdFormat->newPacket();
    cmdFormat->insertDestinationId(destinationId);

    sendEepCommand(cmdFormat);
}

bool D2Eep::processTelegram()
{
    bool ret;

    ret = msgFormat()->getRorg() == EepTelegramFormat::RORG_D2;

    return ret;
}

