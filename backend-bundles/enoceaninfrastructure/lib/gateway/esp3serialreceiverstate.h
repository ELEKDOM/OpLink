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


#ifndef ESP3SERIALRECEIVERSTATE_H
#define ESP3SERIALRECEIVERSTATE_H

#include <QtGlobal>
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{
class Esp3SerialReceiverState
{
private:
    Esp3PacketSerialReceiver& m_receiver;

public:
    Esp3SerialReceiverState(Esp3PacketSerialReceiver& receiver);
    virtual ~Esp3SerialReceiverState();

public:
    virtual void input(quint8 byte) = 0;

protected:
    void initBuffer();
    void populateBufferHeader(quint8 byte);
    bool bufferHeaderPopulated();
    quint8 computeBufferHeaderCrc();
    void initDataBuffer();
    void populateBufferData(quint8 byte);
    bool bufferDataPopulated();
    quint8 computeBufferDataCrc();
    void packetReceived();

protected:
    void wait4SyncByteState();
    void wait4HeaderState();
    void wait4HeaderCrcState();
    void wait4DataState();
    void wait4DataCrcState();
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ESP3SERIALRECEIVERSTATE_H
