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


#include "packet/format/sentformat/eepcommandformat/D2/d201cmd1format.h"
#include "packet/esp3packet.h"

using namespace elekdom::oplink::enocean;

D201Cmd1Format::D201Cmd1Format():
    D201CommandFormat{3, 0x01}
{}

D201Cmd1Format::~D201Cmd1Format()
{

}

void D201Cmd1Format::setOutput(quint8 channel, quint8 val)
{
    QspEsp3Packet& packet{associatedPacket()};
    quint16 offset{2}; // 0 is rorg 1 is Cmd !

    packet->populateData(offset, channel); // channel selection
    packet->populateData(++offset, val); // output value
}
