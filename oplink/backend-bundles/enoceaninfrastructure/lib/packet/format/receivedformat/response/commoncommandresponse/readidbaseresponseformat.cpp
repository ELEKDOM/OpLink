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

#include "packet/format/receivedformat/response/commoncommandresponse/readidbaseresponseformat.h"
#include "packet/esp3packet.h"
#include "gateway/responsehandler.h"

ReadIdBaseResponseFormat::ReadIdBaseResponseFormat()
{

}

ReadIdBaseResponseFormat::ReadIdBaseResponseFormat(const QspEsp3Packet &packet):
    CommonCommandResponseFormat{packet}
{

}

ReadIdBaseResponseFormat::~ReadIdBaseResponseFormat()
{

}

bool ReadIdBaseResponseFormat::baseId(quint32 &val)
{
    bool ret{false};
    const quint8 *data{rawData()};

    ret = data[0] == 0x00; // Return code = OK !
    if (ret)
    {
        val = data[1] << 24;
        val += data[2] << 16;
        val += data[3] << 8;
        val += data[4];
    }

    return ret;
}

bool ReadIdBaseResponseFormat::remainingWriteCycles(quint8 &val)
{
    bool ret{false};
    const quint8 *data{rawData()};

    ret = data[0] == 0x00; // Return code = OK !
    if (ret)
    {
        val = data[5];
    }

    return ret;
}

void ReadIdBaseResponseFormat::accept(ResponseHandler &visitor)
{
    visitor.visit(*this);
}
