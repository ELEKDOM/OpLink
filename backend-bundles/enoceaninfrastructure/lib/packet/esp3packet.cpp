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


#include "packet/esp3packet.h"

using namespace elekdom::oplink::enocean;

Esp3Crc8 Esp3Packet::s_CRC8;

Esp3Packet::Esp3Packet():
    m_data{nullptr}
{
    init();
}

Esp3Packet::~Esp3Packet()
{
    delete[] m_data;
}

/**
 * @brief Esp3Packet::init
 */
void Esp3Packet::init()
{
    initHeader();
    delete[] m_data;
    m_data = nullptr;
    m_data_byte_idx = 0;
}

/**
 * @brief Esp3Packet::populateHeader
 * @param byte
 */
void Esp3Packet::populateHeader(quint8 byte)
{
    if (m_header_byte_idx < HEADER_BYTE_SIZE)
    {
        m_header[m_header_byte_idx++] = byte;
    }
}

bool Esp3Packet::headerPopulated()
{
    return m_header_byte_idx >= HEADER_BYTE_SIZE;
}

void Esp3Packet::initDataBuffer()
{
    delete[] m_data;
    quint32 size = totalLenght();
    m_data_byte_idx = 0;
    m_data = new quint8[size];
}

void Esp3Packet::populateData(quint8 byte)
{
    quint32 total = totalLenght();
    if (m_data_byte_idx < total)
    {
        m_data[m_data_byte_idx++] = byte;
    }
}

void Esp3Packet::populateData(quint32 offset, quint8 byte)
{
    if (offset < totalLenght())
    {
        m_data[offset] = byte;
        m_data_byte_idx = offset + 1;
    }
}

bool Esp3Packet::dataPopulated()
{
    return m_data_byte_idx >= totalLenght();
}

quint16 Esp3Packet::dataLenght()
{
    return m_header[1] + static_cast<unsigned short>(m_header[0]<< 8);
}

quint8 Esp3Packet::optionalLenght()
{
    return m_header[2];
}

quint32 Esp3Packet::totalLenght()
{
    return dataLenght() + optionalLenght();
}

quint8 Esp3Packet::packetType()
{
    return m_header[3];
}

const quint8 *Esp3Packet::rawHeader()
{
    return m_header;
}

const quint8 *Esp3Packet::rawData()
{
    return m_data;
}

QByteArray Esp3Packet::serializeHeader()
{
    QByteArray ret;

    char* header = reinterpret_cast<char*>(const_cast<quint8*>(rawHeader()));
    ret.append(header, HEADER_BYTE_SIZE);
    return ret;
}

QByteArray Esp3Packet::serializeData()
{
    QByteArray ret;

    char* data = reinterpret_cast<char*>(const_cast<quint8*>(rawData()));
    ret.append(data, totalLenght());

    return ret;
}

QByteArray Esp3Packet::logPacket()
{
    QByteArray ret;

    ret += "[";
    ret += serializeHeader().toHex(':');
    ret += "][";
    ret += serializeData().toHex(':');
    ret += "]";

    return ret;
}

QByteArray Esp3Packet::dataFrame()
{
    QByteArray stream;

    // sync byte first!
    stream.append(SYNC_BYTE);

    // header +  crc8
    stream.append(serializeHeader());
    stream.append(computeHeaderCrc());

    // data + crc8
    stream.append(serializeData());
    stream.append(computeDataCrc());

    return stream;
}

quint8 Esp3Packet::computeHeaderCrc()
{
    return s_CRC8.computeCrc(rawHeader(), HEADER_BYTE_SIZE);
}

quint8 Esp3Packet::computeDataCrc()
{
    return s_CRC8.computeCrc(rawData(), totalLenght());
}

void Esp3Packet::initHeader()
{
    for (auto i = 0; i < HEADER_BYTE_SIZE; ++i)
    {
        m_header[i] = 0;
    }
    m_header_byte_idx = 0;
}
