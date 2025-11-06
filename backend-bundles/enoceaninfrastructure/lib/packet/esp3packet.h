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

#ifndef ESP3PACKET_H
#define ESP3PACKET_H

#include <QSharedPointer>
#include <QByteArray>
#include "esp3crc8.h"

class Esp3Packet
{
public:
    Esp3Packet();
    virtual ~Esp3Packet();

public:
    void init();
    void populateHeader(quint8 byte);
    bool headerPopulated();
    void initDataBuffer();
    void populateData(quint8 byte);
    void populateData(quint32 offset, quint8 byte);
    bool dataPopulated();
    quint16 dataLenght();
    quint8 optionalLenght();
    quint32 totalLenght();
    quint8 packetType();
    const quint8 *rawHeader();
    const quint8 *rawData();
    QByteArray serializeHeader();
    QByteArray serializeData();
    QByteArray logPacket();
    QByteArray dataFrame();
    quint8 computeHeaderCrc();
    quint8 computeDataCrc();

private:
    void initHeader();

private:
    static Esp3Crc8 s_CRC8;

public:
    static const quint8 SYNC_BYTE = 0x55;
    static const quint8 HEADER_BYTE_SIZE = 0x04;
    static const quint8 RADIO_ERP1 = 0x01;
    static const quint8 RESPONSE = 0x02;
    static const quint8 RADIO_SUB_TEL = 0x03;
    static const quint8 EVENT = 0x04;
    static const quint8 COMMON_COMMAND = 0x05;

private:
    quint8  m_header[HEADER_BYTE_SIZE];
    quint8  m_header_byte_idx;  // used to populate the header
    quint8 *m_data;
    quint32 m_data_byte_idx;  // used to populate the data
};
using QspEsp3Packet = QSharedPointer<Esp3Packet>;
#endif // ESP3PACKET_H
