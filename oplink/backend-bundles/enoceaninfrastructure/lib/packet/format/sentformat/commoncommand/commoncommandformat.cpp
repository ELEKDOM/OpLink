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

#include "packet/format/sentformat/commoncommand/commoncommandformat.h"
#include "packet/esp3packet.h"

CommonCommandFormat::CommonCommandFormat(quint16 commonCommandDataSize, quint8 optionalLenght, quint8 cmd):
    Esp3SentPacketFormat(0x01 + commonCommandDataSize, optionalLenght, Esp3Packet::COMMON_COMMAND),
    m_cmd{cmd}
{

}

CommonCommandFormat::~CommonCommandFormat()
{

}

void CommonCommandFormat::fillInData()
{
    QspEsp3Packet& packet{associatedPacket()};

    // Command code
    packet->populateData(0x00, m_cmd);
}
