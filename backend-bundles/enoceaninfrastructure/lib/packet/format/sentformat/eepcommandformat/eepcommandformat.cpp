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

#include "packet/format/sentformat/eepcommandformat/eepcommandformat.h"
#include "packet/format/receivedformat/response/eepcommandresponseformat.h"
#include "packet/esp3packet.h"

EepCommandFormat::EepCommandFormat(quint16 dataPayload, quint8 optionalLenght, quint8 rorg):
    Esp3SentPacketFormat(6 + dataPayload, optionalLenght, Esp3Packet::RADIO_ERP1),
    m_dataPayload{dataPayload},
    m_rorg{rorg}
{

}

EepCommandFormat::~EepCommandFormat()
{

}

void EepCommandFormat::insertSenderId(quint32 senderId)
{
    QspEsp3Packet& packet{associatedPacket()};
    quint32 offset(m_dataPayload + 1);
    quint8 byte;

    byte = (senderId >> 24) & 0xFF;
    packet->populateData(offset++, byte);
    byte = (senderId >> 16) & 0xFF;
    packet->populateData(offset++, byte);
    byte = (senderId >> 8) & 0xFF;
    packet->populateData(offset++, byte);
    byte = senderId & 0xFF;
    packet->populateData(offset, byte);
}

void EepCommandFormat::insertDestinationId(quint32 destinationId)
{
    QspEsp3Packet& packet{associatedPacket()};
    quint32 offset(packet->dataLenght() + 1);
    quint8 byte;

    // 0xFFFFFFFF
    //destinationId = 0x058F9269; // test debug !

    byte = (destinationId >> 24) & 0xFF;
    packet->populateData(offset++, byte);
    byte = (destinationId >> 16) & 0xFF;
    packet->populateData(offset++, byte);
    byte = (destinationId >> 8) & 0xFF;
    packet->populateData(offset++, byte);
    byte = destinationId & 0xFF;
    packet->populateData(offset, byte);
}

void EepCommandFormat::fillInData()
{
    QspEsp3Packet& packet{associatedPacket()};

    // RORG
    packet->populateData(0, m_rorg);

    //  Optional Data
    //---------------

    quint32 offset{packet->dataLenght()};

    // SubTelNum
    packet->populateData(offset, 0x03);

    // dBm
    offset += 5; //  data + SubtelNum + Destination ID
    packet->populateData(offset, 0xFF);

    // Security Level
    packet->populateData(++offset, 0x00);
}

QspResponseFormat EepCommandFormat::getExpectedResponseFormat(const QspEsp3Packet &responsePacket)
{
    QspResponseFormat ret{new EepCommandResponseFormat{responsePacket}};
    return ret;
}
