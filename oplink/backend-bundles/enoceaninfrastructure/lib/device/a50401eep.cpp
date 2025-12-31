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

#include <QVariant>
#include "a50401eep.h"
#include "packet/format/receivedformat/eeptelegram/a504telegramformat.h"

A50401Eep::A50401Eep(const oplink::DeviceId &id,
                     oplink::DeviceHook &deviceHook):
    A504Eep{id, deviceHook}
{

}

A50401Eep::~A50401Eep()
{

}

bool A50401Eep::processTelegram()
{
    bool ret{false};
    QspA504TelegramFormat formatA504{(msgFormat()).dynamicCast<A504TelegramFormat>()};

    if (A5Eep::processTelegram())
    {
        if (formatA504->db_0() == 0x0A)
        {
            double val;

            ret = true;
            // channel is always 0 for temperature !
            val = formatA504->db_1();
            val *= 0.16;
            setChannelValue(0, QVariant(val));

            // channel is always 1 for humidity !
            val = formatA504->db_2();
            val *= 0.4;
            setChannelValue(1, QVariant(val));
        }
    }

    return ret;
}
