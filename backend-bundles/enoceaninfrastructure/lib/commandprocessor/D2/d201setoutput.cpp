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


#include "d201setoutput.h"
#include "command/command-names.h"
#include "command/command.h"
#include "abstract_infrastructure/device/device.h"
#include "packet/format/sentformat/eepcommandformat/D2/d201cmd1format.h"

using namespace elekdom::oplink::enocean;

D201SetOutput::D201SetOutput(const core::infrastructure::QspDevice &device):
    D201CommandProcessor{device, new D201Cmd1Format}
{

}

D201SetOutput::~D201SetOutput()
{

}

bool D201SetOutput::completePacket(core::command::QspCommand order)
{
    bool ret;
    const core::observable::PropertyName& pname{order->property()};
    int idx;
    quint8 valOutput;

    ret = getChannelIdx(pname, idx);
    if (ret)
    {
        QVariant val{order->value()};

        ret = val.isValid();
        if (ret)
        {
            QString state{val.toString()};

            if (state == core::command::CommandArgs::ON)
            {
                valOutput = 0x64;
            }
            else if (state == core::command::CommandArgs::OFF)
            {
                valOutput = 0x00;
            }
            else
            {
                ret = false;
            }
        }

    }

    if (ret)
    {
        setOutput(idx, valOutput);
    }


    return ret;
}

void D201SetOutput::setOutput(quint8 channel, quint8 val)
{
    QspEepCommandFormat& eepCmdFormat{sentCommandFormat()};
    QspD201Cmd1Format cmd1Format{eepCmdFormat.dynamicCast<D201Cmd1Format>()};

    cmd1Format->setOutput(channel, val);
}

