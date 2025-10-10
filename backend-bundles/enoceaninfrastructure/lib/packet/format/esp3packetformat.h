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


#ifndef ESP3PACKETFORMAT_H
#define ESP3PACKETFORMAT_H

#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class Esp3PacketFormat
{
public:
    Esp3PacketFormat();
    Esp3PacketFormat(const QspEsp3Packet& packet);
    virtual ~Esp3PacketFormat();

public: 
    QspEsp3Packet getPacket() {return m_associatedPacket;}
    QspEsp3Packet& associatedPacket() {return m_associatedPacket;}

private:
    QspEsp3Packet m_associatedPacket;
};

}//namespace bundleTemplate
}//namespace oplink
}//namespace enocean

#endif // ESP3PACKETFORMAT_H
