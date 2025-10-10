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


#ifndef ESP3SENTPACKETFORMAT_H
#define ESP3SENTPACKETFORMAT_H

#include "packet/format/esp3packetformat.h"
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class Esp3SentPacketFormat : public Esp3PacketFormat
{
public:
    Esp3SentPacketFormat(quint16 dataLenght,quint8 optionalLenght,quint8 packetType);
    ~Esp3SentPacketFormat() override;

public:
    void newPacket();
    virtual QspResponseFormat getExpectedResponseFormat(const QspEsp3Packet& responsePacket) = 0;
    QByteArray logPacket();

protected:
    virtual void fillInData()= 0;

private:
    void fillInHeader();

private:
    quint16 m_dataLenght;
    quint8  m_optionalLenght;
    quint8  m_packetType;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ESP3SENTPACKETFORMAT_H
