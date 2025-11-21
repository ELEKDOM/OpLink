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

#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"
#include "packet/esp3packet.h"

EepTelegramFormat::EepTelegramFormat()
{

}

EepTelegramFormat::EepTelegramFormat(const QspEsp3Packet &packet):
Esp3ReceivedPacketFormat{packet}
{

}

EepTelegramFormat::~EepTelegramFormat()
{

}

void EepTelegramFormat::setPacket(const QspEsp3Packet &packet)
{
    replacePacket(packet);
}

EepTelegramFormat::EID EepTelegramFormat::getSenderId()
{
    const quint8 *data{associatedPacket()->rawData()};
    quint16 offset = associatedPacket()->dataLenght() - 5; // 5 = sender id + status

    QByteArray array;
    array.append(data[offset]);
    array.append(data[offset + 1]);
    array.append(data[offset + 2]);
    array.append(data[offset + 3]);

    return array.toHex();
}

quint8 EepTelegramFormat::getRorg()
{
    const quint8 *data{associatedPacket()->rawData()};

    return data[0];
}
