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
#include "gateway/esp3packetserialreceiver.h"
#include "enoceaninfrastructurelogchannel.h"

Esp3PacketSerialReceiver::Esp3PacketSerialReceiver(QObject *parent):
    Esp3PacketReceiver{parent},
    m_curState{&m_wait4SyncByte},
    m_wait4SyncByte{*this},
    m_wait4Header{*this},
    m_wait4HeaderCrc{*this},
    m_wait4Data{*this},
    m_wait4DataCrc{*this}
{

}

Esp3PacketSerialReceiver::~Esp3PacketSerialReceiver()
{

}

void Esp3PacketSerialReceiver::input(quint8 byte)
{
    pfDebug7(s_EnoceanLogChannel) << Qt::hex << byte;
    m_curState->input(byte);
}

