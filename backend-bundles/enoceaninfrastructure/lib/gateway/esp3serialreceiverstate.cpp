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

#include "gateway/esp3serialreceiverstate.h"
#include "gateway/esp3packetserialreceiver.h"

Esp3SerialReceiverState::Esp3SerialReceiverState(Esp3PacketSerialReceiver& receiver):
    m_receiver{receiver}
{

}

Esp3SerialReceiverState::~Esp3SerialReceiverState()
{

}

void Esp3SerialReceiverState::initBuffer()
{
    m_receiver.initBuffer();
}

void Esp3SerialReceiverState::populateBufferHeader(quint8 byte)
{
    m_receiver.populateBufferHeader(byte);
}

bool Esp3SerialReceiverState::bufferHeaderPopulated()
{
    return m_receiver.bufferHeaderPopulated();
}

quint8 Esp3SerialReceiverState::computeBufferHeaderCrc()
{
    return m_receiver.computeBufferHeaderCrc();
}

void Esp3SerialReceiverState::initDataBuffer()
{
    m_receiver.initDataBuffer();
}

void Esp3SerialReceiverState::populateBufferData(quint8 byte)
{
    m_receiver.populateBufferData(byte);
}

bool Esp3SerialReceiverState::bufferDataPopulated()
{
    return m_receiver.bufferDataPopulated();
}

quint8 Esp3SerialReceiverState::computeBufferDataCrc()
{
    return m_receiver.computeBufferDataCrc();
}

void Esp3SerialReceiverState::packetReceived()
{
    m_receiver.receivingPacket();
}

void Esp3SerialReceiverState::wait4SyncByteState()
{
    m_receiver.wait4SyncByteState();
}

void Esp3SerialReceiverState::wait4HeaderState()
{
    m_receiver.wait4HeaderState();
}

void Esp3SerialReceiverState::wait4HeaderCrcState()
{
    m_receiver.wait4HeaderCrcState();
}

void Esp3SerialReceiverState::wait4DataState()
{
    m_receiver.wait4DataState();
}

void Esp3SerialReceiverState::wait4DataCrcState()
{
    m_receiver.wait4DataCrcState();
}


