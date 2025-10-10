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
#include "gateway/waitforheadercrc.h"
#include "enoceaninfrastructurelogchannel.h"

using namespace elekdom::oplink::enocean;

WaitForHeaderCrc::WaitForHeaderCrc(Esp3PacketSerialReceiver& receiver):
    Esp3SerialReceiverState{receiver}
{

}

WaitForHeaderCrc::~WaitForHeaderCrc()
{

}

void WaitForHeaderCrc::input(quint8 byte)
{
    if (byte == computeBufferHeaderCrc())
    {
        initDataBuffer();
        wait4DataState();
    }
    else
    {
        pfWarning7(s_EnoceanLogChannel) << QObject::tr("WaitForHeaderCrc : le CRC du header n'est pas valide");
        initBuffer();
        wait4SyncByteState();
    }
}
