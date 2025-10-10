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
#include "gateway/waitfordatacrc.h"
#include "enoceaninfrastructurelogchannel.h"

using namespace elekdom::oplink::enocean;

WaitForDataCrc::WaitForDataCrc(Esp3PacketSerialReceiver& receiver):
    Esp3SerialReceiverState{receiver}
{

}

WaitForDataCrc::~WaitForDataCrc()
{

}

void WaitForDataCrc::input(quint8 byte)
{
    if (byte == computeBufferDataCrc())
    {
        // Notify a new rawpacket to process
        packetReceived();
    }
    else
    {
        // Reset the packet's content
        pfWarning7(s_EnoceanLogChannel) << QObject::tr("WaitForDataCrc : le CRC des données n'est pas valide");
        initBuffer();
    }
    wait4SyncByteState();
}
