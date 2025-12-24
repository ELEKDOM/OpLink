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
#include "d2010ceep.h"
#include "packet/format/sentformat/eepcommandformat/D2/d201cmd9format.h"
#include "packet/format/sentformat/eepcommandformat/D2/d201cmd6format.h"
#include "packet/format/receivedformat/eeptelegram/d201telegramformat.h"

D2010CEep::D2010CEep(const oplink::DeviceId &id,
                     oplink::DeviceHook &deviceHook):
    D201Eep{id, deviceHook}
{

}

D2010CEep::~D2010CEep()
{

}

bool D2010CEep::processTelegram()
{
    bool ret{false};
    QspD201TelegramFormat formatD2010C{(msgFormat()).dynamicCast<D201TelegramFormat>()};

    if (D2Eep::processTelegram())
    {
        if (!msgCmd0A(formatD2010C, ret))
        {
            msgCmd07(formatD2010C, ret);
        }
    }

    return ret;
}

void D2010CEep::recoverState()
{
    // For a pilot wire module, a command "Actuator Pilot Wire Mode Query" must be send to device
    QspD201Cmd9Format cmdPwmFormat{new D201Cmd9Format};
    qint32 destinationId{id().toInt(nullptr, 16)};

    cmdPwmFormat->newPacket();
    cmdPwmFormat->insertDestinationId(destinationId);

    sendEepCommand(cmdPwmFormat);

    // D2010C also allows consumption to be recovered !
    QspD201Cmd6Format cmdMeasFormat{new D201Cmd6Format};

    cmdMeasFormat->newPacket();
    cmdMeasFormat->insertDestinationId(destinationId);

    sendEepCommand(cmdMeasFormat);
}

