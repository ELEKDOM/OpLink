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


#include "d201statusquery.h"
#include "command/command.h"
#include "packet/format/sentformat/eepcommandformat/D2/d201cmd3format.h"

using namespace elekdom::oplink::enocean;

D201StatusQuery::D201StatusQuery(const core::infrastructure::QspDevice &device):
    D201CommandProcessor{device, new D201Cmd3Format}
{

}

D201StatusQuery::~D201StatusQuery()
{

}

bool D201StatusQuery::completePacket(core::command::QspCommand order)
{
    // No arg for CMD 0x03 !
    Q_UNUSED(order)
    return true;
}
