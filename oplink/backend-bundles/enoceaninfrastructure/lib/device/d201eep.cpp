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
#include "d201eep.h"

D201Eep::D201Eep(const oplink::DeviceId& id,
                 oplink::DeviceHook& deviceHook):
    D2Eep{id, deviceHook, new D201TelegramFormat}
{

}

D201Eep::~D201Eep()
{

}

bool D201Eep::msgCmd04(QspD201TelegramFormat &telFormat, bool &processed)
{
    bool ret;

    processed = ret = false;
    if (telFormat->isCmdActuatorStatusResponse())
    {
        quint8 channel;
        bool   value;

        ret = true;
        if (telFormat->getActuatorStatus(channel, value))
        {
            processed = true;
            setChannelValue(channel, QVariant(value));
        }
    }

    return ret;
}

bool D201Eep::msgCmd07(QspD201TelegramFormat &telFormat, bool &processed)
{
    bool ret;

    processed = ret = false;
    if (telFormat->isCmdActuatorMeasurementResponse() && hasChannel(1))
    {
        quint8 eo_channel;
        quint32 measurement;
        QString unit;

        ret = true;
        if(telFormat->getActuatorMeasurementValue(eo_channel,measurement,unit))
        {
            //D2010C has only one channel
            if (eo_channel == 0x00)
            {
                processed = true;
                // channel is always 1 for measurement !
                setChannelValue(1, QVariant(measurement));
                // channel is always 2 for unit !
                setChannelValue(2, QVariant(unit));
            }
        }
    }

    return ret;
}

bool D201Eep::msgCmd0A(QspD201TelegramFormat &telFormat, bool &processed)
{
    bool ret;

    processed = ret = false;
    if (telFormat->isCmdActuatorPilotWireModeResponse())
    {
        quint8   mode;

        ret = true;
        if (telFormat->getActuatorPilotWireMode(mode))
        {
            processed = true;
            // channel is always 0 for pwm !
            setChannelValue(0, QVariant(mode));
        }
    }

    return ret;
}
