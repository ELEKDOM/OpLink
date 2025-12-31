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

#ifndef ESP3RECEIVEDPACKETFORMAT_H
#define ESP3RECEIVEDPACKETFORMAT_H

#include "packet/format/esp3packetformat.h"

class Esp3ReceivedPacketFormat : public Esp3PacketFormat
{
public:
    Esp3ReceivedPacketFormat();
    Esp3ReceivedPacketFormat(const QspEsp3Packet& packet);
    ~Esp3ReceivedPacketFormat() override;

protected:
   void replacePacket(const QspEsp3Packet& packet);
   const quint8 *rawData();
};

#endif // ESP3RECEIVEDPACKETFORMAT_H
