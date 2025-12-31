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

#include "d201setpilotwiremode.h"
#include "command/command-names.h"
#include "command/command.h"
#include "packet/format/sentformat/eepcommandformat/D2/d201cmd8format.h"

D201SetPilotWireMode::D201SetPilotWireMode(const oplink::QspDevice &device):
    D201CommandProcessor{device, new D201Cmd8Format}
{

}

D201SetPilotWireMode::~D201SetPilotWireMode()
{

}

bool D201SetPilotWireMode::completePacket(oplink::QspCommand order)
{
    bool ret;
    const oplink::PropertyName& pname{order->property()};
    int idx;
    quint8 mode;

    ret = getChannelIdx(pname, idx);
    if (ret && idx == 0)
    {
        QVariant val{order->value()};

        ret = val.isValid();
        if (ret)
        {
            QString pwm{val.toString()};

            if (pwm == oplink::CommandArgs::OFF)
            {
                mode = 0x00;
            }
            else if (pwm == oplink::CommandArgs::COMFORT)
            {
                mode = 0x01;
            }
            else if (pwm == oplink::CommandArgs::COMFORT_1)
            {
                mode = 0x04;
            }
            else if (pwm == oplink::CommandArgs::COMFORT_2)
            {
                mode = 0x05;
            }
            else if (pwm == oplink::CommandArgs::ECO)
            {
                mode = 0x02;
            }
            else if (pwm == oplink::CommandArgs::NOFROST)
            {
                mode = 0x03;
            }
            else
            {
                ret = false;
            }
        }

        if (ret)
        {
            setMode(mode);
        }
    }

    return ret;
}

void D201SetPilotWireMode::setMode(quint8 mode)
{
    QspEepCommandFormat& eepCmdFormat{sentCommandFormat()};
    QspD201Cmd8Format cmd8Format{eepCmdFormat.dynamicCast<D201Cmd8Format>()};

    cmd8Format->setMode(mode);
}
