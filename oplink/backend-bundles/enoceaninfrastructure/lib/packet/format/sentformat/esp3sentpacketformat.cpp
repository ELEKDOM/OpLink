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

#include "packet/format/sentformat/esp3sentpacketformat.h"
#include "packet/esp3packet.h"

Esp3SentPacketFormat::Esp3SentPacketFormat(quint16 dataLenght, quint8 optionalLenght, quint8 packetType):
    m_dataLenght{dataLenght},
    m_optionalLenght{optionalLenght},
    m_packetType{packetType}
{

}

Esp3SentPacketFormat::~Esp3SentPacketFormat()
{

}

void Esp3SentPacketFormat::newPacket()
{
    associatedPacket().reset(new Esp3Packet);
    fillInHeader();
    associatedPacket()->initDataBuffer();
    fillInData();
}

QByteArray Esp3SentPacketFormat::logPacket()
{
    return associatedPacket()->logPacket();
}

void Esp3SentPacketFormat::fillInHeader()
{
    QspEsp3Packet& packet{associatedPacket()};

    quint8 byte;

    // Data length
    byte = m_dataLenght >> 8;
    packet->populateHeader(byte);
    byte = m_dataLenght & 0x0F;
    packet->populateHeader(byte);

    // Option length
    byte = m_optionalLenght;
    packet->populateHeader(byte);

    // Packet type
    byte = m_packetType;
    packet->populateHeader(byte);
}

