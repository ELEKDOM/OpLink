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


#include "packet/format/receivedformat/esp3receivedpacketformat.h"
#include "packet/esp3packet.h"

using namespace elekdom::oplink::enocean;

Esp3ReceivedPacketFormat::Esp3ReceivedPacketFormat()
{

}

Esp3ReceivedPacketFormat::Esp3ReceivedPacketFormat(const QspEsp3Packet &packet):
    Esp3PacketFormat{packet}
{

}

Esp3ReceivedPacketFormat::~Esp3ReceivedPacketFormat()
{

}

void Esp3ReceivedPacketFormat::replacePacket(const QspEsp3Packet &packet)
{
    associatedPacket() = packet;
}

const quint8 *Esp3ReceivedPacketFormat::rawData()
{
    return associatedPacket()->rawData();
}
