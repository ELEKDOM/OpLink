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


#ifndef EEPTELEGRAMFORMAT_H
#define EEPTELEGRAMFORMAT_H

#include "packet/format/receivedformat/esp3receivedpacketformat.h"
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class EepTelegramFormat : public Esp3ReceivedPacketFormat
{
public:
    using EID = QByteArray;

public:
    EepTelegramFormat();
    EepTelegramFormat(const QspEsp3Packet& packet);
    ~EepTelegramFormat() override;

public:
    void setPacket(const QspEsp3Packet& packet);
    EID getSenderId();
    quint8 getRorg();

public:
    static const quint8 RORG_D2 = 0xD2;
    static const quint8 RORG_D5 = 0xD5;
    static const quint8 RORG_A5 = 0xA5;
    static const quint8 RORG_F6 = 0xF6;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // EEPTELEGRAMFORMAT_H
