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


#include "d201cmd3format.h"
#include "packet/esp3packet.h"

using namespace elekdom::oplink::enocean;

D201Cmd3Format::D201Cmd3Format():
    D201CommandFormat{2, 0x03}
{

}

D201Cmd3Format::~D201Cmd3Format()
{

}

void D201Cmd3Format::fillInData()
{
    QspEsp3Packet& packet{associatedPacket()};

    // Base command general fill in
    D2CommandFormat::fillInData();

    // Ask for all output channel
    packet->populateData(2, 0x1E);
}
