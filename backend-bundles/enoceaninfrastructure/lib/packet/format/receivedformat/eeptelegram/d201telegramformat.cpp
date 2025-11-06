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

#include "packet/format/receivedformat/eeptelegram/d201telegramformat.h"
#include "observable/values.h"

D201TelegramFormat::D201TelegramFormat()
{

}

D201TelegramFormat::~D201TelegramFormat()
{

}

bool D201TelegramFormat::isCmdActuatorStatusResponse()
{
    bool ret;

    ret = CMD_ACTUATOR_STATUS_RESPONSE == getCmd();
    return ret;
}

bool D201TelegramFormat::getActuatorStatus(quint8 &channel, bool &value)
{
    bool ret {true};
    const quint8 *data{rawData()};
    quint8 output_val;

    output_val = data[3] & 0x7F;
    channel = data[2] & 0x1F;
    if (output_val > 0x64 || channel > 0x1D)
    {
        ret = false;
    }
    else
    {
        if (output_val > 0)
        {
            value = oplink::Values::STATE_ON;
        }
        else
        {
            value = oplink::Values::STATE_OFF;
        }
    }

    return ret;
}

bool D201TelegramFormat::isCmdActuatorMeasurementResponse()
{
    bool ret;

    ret = CMD_ACTUATOR_MEASUREMENT_RESPONSE == getCmd();
    return ret;
}

bool D201TelegramFormat::getActuatorMeasurementValue(quint8& channel, quint32 &value, QString &unit)
{
    bool ret {false};
    const quint8 *data{rawData()};
    quint8 val;

    // unit
    //-----
    val = data[2] & 0xE0;
    val >>= 5;
    if (val == 0x00)
    {
        ret = true;
        unit = oplink::Values::ENERGY_Ws;
    }
    else if (val == 0x01)
    {
        ret = true;
        unit = oplink::Values::ENERGY_Wh;
    }
    else if (val == 0x02)
    {
        ret = true;
        unit = oplink::Values::ENERGY_KWh;
    }
    else if (val == 0x03)
    {
        ret = true;
        unit = oplink::Values::POWER_W;
    }
    else if (val == 0x04)
    {
        ret = true;
        unit = oplink::Values::POWER_KW;
    }

    if (ret)
    {
        // Channel
        //--------
        val = data[2] & 0x1F;
        if (val < 0x1E)
        {
            channel = val;
        }
        else
        {
            ret = false;
        }

        if (ret)
        {
            // Measurement
            //------------
            quint32 measurement;
            quint8 *ptr8 = (quint8*)&measurement;

            *ptr8 = data[6];
            *(++ptr8) = data[5];
            *(++ptr8) = data[4];
            *(++ptr8) = data[3];

            value = measurement;
        }
    }

    return ret;
}

bool D201TelegramFormat::isCmdActuatorPilotWireModeResponse()
{
    bool ret;

    ret = CMD_ACTUATOR_PILOT_WIRE_MODE_RESPONSE == getCmd();
    return ret;
}

bool D201TelegramFormat::getActuatorPilotWireMode(quint8 &mode)
{
    bool ret {false};
    const quint8 *data{rawData()};
    quint8 mode_val;

    mode_val = data[2] & 0x07;

    if (mode_val == 0x00)
    {
        ret = true;
        mode = oplink::Values::PW_MODE_STOP;
    }
    else if (mode_val == 0x01)
    {
        ret = true;
        mode = oplink::Values::PW_MODE_COMFORT;
    }
    else if (mode_val == 0x02)
    {
        ret = true;
        mode = oplink::Values::PW_MODE_ECO;
    }
    else if (mode_val == 0x03)
    {
        ret = true;
        mode = oplink::Values::PW_MODE_ANTI_FREEZE;
    }
    else if (mode_val == 0x04)
    {
        ret = true;
        mode = oplink::Values::PW_MODE_COMFORT_1;
    }
    else if (mode_val == 0x05)
    {
        ret = true;
        mode = oplink::Values::PW_MODE_COMFORT_2;
    }

    return ret;
}

quint8 D201TelegramFormat::getCmd()
{
    const quint8 *data{rawData()};

    quint8 ret = data[1] & 0x0F; // [0] is RORG !
    return ret;
}
