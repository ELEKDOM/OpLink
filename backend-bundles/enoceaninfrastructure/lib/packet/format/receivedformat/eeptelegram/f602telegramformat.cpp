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


#include "packet/format/receivedformat/eeptelegram/f602telegramformat.h"

using namespace elekdom::oplink::enocean;

F602TelegramFormat::F602TelegramFormat()
{

}

F602TelegramFormat::~F602TelegramFormat()
{

}

quint8 F602TelegramFormat::statusByte()
{
    const quint8 *data{rawData()};
    return data[6];
}

bool F602TelegramFormat::buttonState(quint8 &channel, bool &value)
{
    bool ret{false};
    quint8 N_message{statusByte()};

    if ((N_message & 0x30) == 0x30)
    {
        quint8 button{dataByte()};
        quint8 pressed{button};

        button &= 0xE0;
        pressed &= 0X10;

        if (button == 0x00 || button == 0x20)
        {
            channel = 0;
            if (pressed)
            {
                ret = true;
                if (button == 0x00)
                { // AI
                  value = true;
                }
                else
                {
                  // AO
                  value = false;
                }
            }
        }
        else if (button == 0x40 || button == 0x60)
        {
            channel = 1;
            if (pressed)
            {
                ret = true;
                if (button == 0x40)
                { // BI
                  value = true;
                }
                else
                {
                  // BO
                  value = false;
                }
            }
        }
    }
    return ret;
}
