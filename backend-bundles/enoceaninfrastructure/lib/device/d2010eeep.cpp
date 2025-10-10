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
#include "d2010eeep.h"
#include "packet/format/receivedformat/eeptelegram/d201telegramformat.h"

using namespace elekdom::oplink::enocean;

D2010EEep::D2010EEep(const core::infrastructure::DeviceId &id,
                     core::infrastructure::DeviceHook &deviceHook):
    D201Eep{id, deviceHook}
{

}

D2010EEep::~D2010EEep()
{

}

bool D2010EEep::processTelegram()
{
    bool ret{false};
    QspD201TelegramFormat formatD201OE{(msgFormat()).dynamicCast<D201TelegramFormat>()};

    if (D2Eep::processTelegram())
    {
        if (!msgCmd04(formatD201OE, ret))
        {
            msgCmd07(formatD201OE, ret);
        }
    }

    return ret;
}
