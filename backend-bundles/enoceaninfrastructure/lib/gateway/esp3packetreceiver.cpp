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

#include "logger/pflog.h"
#include "gateway/esp3packetreceiver.h"
#include "enoceaninfrastructurelogchannel.h"
#include "packet/esp3packet.h"

using namespace elekdom::oplink::enocean;

Esp3PacketReceiver::Esp3PacketReceiver(QObject *parent) : QObject{parent},
    m_buffer{new Esp3Packet}
{

}

Esp3PacketReceiver::~Esp3PacketReceiver()
{

}

void Esp3PacketReceiver::receivingPacket()
{
    pfInfo3(s_EnoceanMsgChannel) << "< " << m_buffer->logPacket();

    emit packetReceived(m_buffer);
    m_buffer.reset(new Esp3Packet);
}

void Esp3PacketReceiver::initBuffer()
{
    m_buffer->init();
}

void Esp3PacketReceiver::populateBufferHeader(quint8 byte)
{
    m_buffer->populateHeader(byte);
}

bool Esp3PacketReceiver::bufferHeaderPopulated()
{
    return m_buffer->headerPopulated();
}

quint8 Esp3PacketReceiver::computeBufferHeaderCrc()
{
    return m_buffer->computeHeaderCrc();
}

void Esp3PacketReceiver::initDataBuffer()
{
    m_buffer->initDataBuffer();
}

void Esp3PacketReceiver::populateBufferData(quint8 byte)
{
    m_buffer->populateData(byte);
}

bool Esp3PacketReceiver::bufferDataPopulated()
{
    return m_buffer->dataPopulated();
}

quint8 Esp3PacketReceiver::computeBufferDataCrc()
{
    return m_buffer->computeDataCrc();
}
