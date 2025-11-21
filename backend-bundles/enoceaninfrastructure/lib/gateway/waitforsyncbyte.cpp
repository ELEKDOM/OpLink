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

#include "logger/pflog.h"
#include "gateway/waitforsyncbyte.h"
#include "packet/esp3packet.h"
#include "enoceaninfrastructurelogchannel.h"

WaitForSyncByte::WaitForSyncByte(Esp3PacketSerialReceiver& receiver):
    Esp3SerialReceiverState{receiver}
{

}

WaitForSyncByte::~WaitForSyncByte()
{

}

void WaitForSyncByte::input(quint8 byte)
{
    if (byte == Esp3Packet::SYNC_BYTE)
    {
        initBuffer();
        wait4HeaderState();
    }
    else
    {
        pfWarning7(s_EnoceanLogChannel) << QObject::tr("WaitForSyncByte : valeur erronnée, 0x") << Qt::hex << byte;
    }
}
