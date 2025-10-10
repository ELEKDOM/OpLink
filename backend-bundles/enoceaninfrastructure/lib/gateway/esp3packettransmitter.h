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


#ifndef ESP3PACKETTRANSMITTER_H
#define ESP3PACKETTRANSMITTER_H

#include <QQueue>
#include <QTimer>
#include <QMutex>
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class Esp3PacketTransmitter : public QObject
{
    Q_OBJECT

public:
    Esp3PacketTransmitter(QObject *parent = nullptr);
    ~Esp3PacketTransmitter() override;

signals:
    void sendPacket(elekdom::oplink::enocean::QspEsp3Packet paquet);
    void sendRequest(elekdom::oplink::enocean::QspEsp3SentPacketFormat packet2sendFormat);

public:
    void sendPaquetRequest(QspEsp3SentPacketFormat packet2sendFormat);
    QspResponseFormat getExpectedResponseformat(const QspEsp3Packet& responsePacket);

public slots:
    void onResponseProcessed(bool resendPacket);

private slots:
    void onTimeOut();
    void onSendRequest(elekdom::oplink::enocean::QspEsp3SentPacketFormat packet2sendFormat);

private:
    void startWatchDog();
    void stopWatchDog();
    void sendHead();
    void emitPacket(QspEsp3Packet packet);

private:
    static const int s_time = 300;

private:
    QQueue<QspEsp3SentPacketFormat> m_sendingRequestQueue;
    QTimer                         *m_watchDog;
    QMutex                          m_mutex;
};

}//namespace enocean
}//namespace oplink
}//namespace enocean

#endif // ESP3PACKETTRANSMITTER_H
