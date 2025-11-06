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

#ifndef ESP3PACKETRECEIVER_H
#define ESP3PACKETRECEIVER_H

#include <QObject>
#include <QSharedPointer>
#include "packet/esp3packet.h"

class Esp3PacketReceiver : public QObject
{
    Q_OBJECT

public:
    Esp3PacketReceiver(QObject *parent = nullptr);
    ~Esp3PacketReceiver() override;

signals:
    void packetReceived(QspEsp3Packet packet);

protected:
    void receivingPacket();

protected:
    void initBuffer();
    void populateBufferHeader(quint8 byte);
    bool bufferHeaderPopulated();
    quint8 computeBufferHeaderCrc();
    void initDataBuffer();
    void populateBufferData(quint8 byte);
    bool bufferDataPopulated();
    quint8 computeBufferDataCrc();

private:
    QspEsp3Packet m_buffer;
};
using QspEsp3PacketReceiver = QSharedPointer<Esp3PacketReceiver>;
#endif // ESP3PACKETRECEIVER_H
