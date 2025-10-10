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


#include "d500telegramformat.h"

using namespace elekdom::oplink::enocean;

D500TelegramFormat::D500TelegramFormat() {}

D500TelegramFormat::~D500TelegramFormat()
{

}

bool D500TelegramFormat::contactState(bool& state)
{
    bool ret{false};

    const quint8 *data{rawData()};
    quint8 val{data[1]}; // data[0] is RORG

    if (val == 0x08)
    {
        ret = true;
        state = false; // open
    }
    else if (val == 0x09)
    {
        ret = true;
        state = true; // closed
    }

    return ret;
}
