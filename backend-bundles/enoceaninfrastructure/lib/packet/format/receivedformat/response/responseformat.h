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

#ifndef RESPONSEFORMAT_H
#define RESPONSEFORMAT_H

#include <QSharedPointer>
#include "packet/format/receivedformat/esp3receivedpacketformat.h"
#include "enoceaninfrastructure_forward.h"

class ResponseFormat : public Esp3ReceivedPacketFormat
{
public:
    ResponseFormat();
    ResponseFormat(const QspEsp3Packet& packet);
    ~ResponseFormat() override;

public:
    virtual void accept(ResponseHandler& visitor) = 0;
    quint8 returnCode();

public:
    static const quint8 RET_OK = 0x00;
    static const quint8 RET_ERROR = 0x01;
    static const quint8 RET_NOT_SUPPORTED = 0x02;
    static const quint8 RET_WRONG_PARAM = 0x03;
    static const quint8 RET_OPERATION_DENIED = 0x04;
    static const quint8 RET_LOCK_SET = 0x05;
    static const quint8 RET_BUFFER_TO_SMALL = 0x06;
    static const quint8 RET_NO_FREE_BUFFER = 0x07;
};
using QspResponseFormat = QSharedPointer<ResponseFormat>;
#endif // RESPONSEFORMAT_H
