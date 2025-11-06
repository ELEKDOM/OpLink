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

#ifndef ESP3PACKETSERIALRECEIVER_H
#define ESP3PACKETSERIALRECEIVER_H

#include "esp3packetreceiver.h"
#include "waitforsyncbyte.h"
#include "waitforheader.h"
#include "waitforheadercrc.h"
#include "waitfordata.h"
#include "waitfordatacrc.h"

class Esp3SerialReceiverState;
class Esp3PacketSerialReceiver : public Esp3PacketReceiver
{
    Q_OBJECT

    friend class Esp3SerialReceiverState;

private:
    Esp3SerialReceiverState *m_curState;
    WaitForSyncByte          m_wait4SyncByte;
    WaitForHeader            m_wait4Header;
    WaitForHeaderCrc         m_wait4HeaderCrc;
    WaitForData              m_wait4Data;
    WaitForDataCrc           m_wait4DataCrc;

public:
    Esp3PacketSerialReceiver(QObject *parent = nullptr);
    ~Esp3PacketSerialReceiver() override;

public slots:
    void input(quint8 byte);

protected:
    void wait4SyncByteState() {m_curState = &m_wait4SyncByte;}
    void wait4HeaderState() {m_curState = &m_wait4Header;}
    void wait4HeaderCrcState() {m_curState = &m_wait4HeaderCrc;}
    void wait4DataState(){m_curState = &m_wait4Data;}
    void wait4DataCrcState(){m_curState = &m_wait4DataCrc;}
};

#endif // ESP3PACKETSERIALRECEIVER_H
