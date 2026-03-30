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

#include <QMutexLocker>
#include "logger/pflog.h"
#include "gateway/esp3packettransmitter.h"
#include "packet/format/sentformat/esp3sentpacketformat.h"
#include "packet/format/receivedformat/response/responseformat.h"
#include "packet/esp3packet.h"
#include "enoceaninfrastructurelogchannel.h"

Esp3PacketTransmitter::Esp3PacketTransmitter(QObject *parent):
    QObject{parent},
    m_watchDog{new QTimer(this)}
{
    m_watchDog->setInterval(s_time);
    bool ok = connect(m_watchDog, SIGNAL(timeout()), SLOT(onTimeOut()));
    if (!ok)
    {
        pfWarning8(s_EnoceanLogChannel) << tr("Echec de connexion du watchDog !");
    }

    ok = connect(this,
                 SIGNAL(sendRequest(elekdom::oplink::enocean::QspEsp3SentPacketFormat)),
                 SLOT(onSendRequest(elekdom::oplink::enocean::QspEsp3SentPacketFormat)),
                 Qt::QueuedConnection);
    if (!ok)
    {
        pfWarning8(s_EnoceanLogChannel) << tr("Echec de connexion du siganl sendRequest !");
    }
}

Esp3PacketTransmitter::~Esp3PacketTransmitter()
{
    delete m_watchDog;
}

void Esp3PacketTransmitter::sendPaquetRequest(QspEsp3SentPacketFormat packet2sendFormat)
{
    pfDebug3(s_EnoceanLogChannel) << "->Esp3PacketTransmitter::sendPaquetRequest ";

    emit sendRequest(packet2sendFormat);

    pfDebug3(s_EnoceanLogChannel) << "<-Esp3PacketTransmitter::sendPaquetRequest ";
}

QspResponseFormat Esp3PacketTransmitter::getExpectedResponseformat(const QspEsp3Packet& responsePacket)
{
    QspResponseFormat ret;

    QMutexLocker lock(&m_mutex);

    if (!m_sendingRequestQueue.isEmpty())
    {
        ret = (m_sendingRequestQueue.head())->getExpectedResponseFormat(responsePacket);
    }

    return ret;
}

void Esp3PacketTransmitter::onResponseProcessed(bool resendPacket)
{
    pfDebug3(s_EnoceanLogChannel) << "->Esp3PacketTransmitter::onResponseProcessed " << resendPacket;

    pfDebug6(s_EnoceanLogChannel) << "Esp3PacketTransmitter::onResponseProcessed ";
    QMutexLocker lock(&m_mutex);

    stopWatchDog();
    if(!resendPacket)
    {
        QspEsp3SentPacketFormat lastSend{dequeue()};
    }  
    sendHead();

    pfDebug3(s_EnoceanLogChannel) << "<-Esp3PacketTransmitter::onResponseProcessed ";
}

void Esp3PacketTransmitter::onTimeOut()
{
    QMutexLocker lock(&m_mutex);

    stopWatchDog();
    pfWarning6(s_EnoceanLogChannel) << tr("PacketTransmitter timeout !");

    QspEsp3SentPacketFormat  pFormat{dequeue()};

    sendHead();
}

void Esp3PacketTransmitter::onSendRequest(QspEsp3SentPacketFormat packet2sendFormat)
{
    pfDebug3(s_EnoceanLogChannel) << "->Esp3PacketTransmitter::onSendRequest ";

    pfDebug5(s_EnoceanLogChannel) << "Esp3PacketTransmitter::onSendRequest " << packet2sendFormat->logPacket();

    QMutexLocker lock(&m_mutex);

    if (m_sendingRequestQueue.isEmpty())
    {
        emitPacket(packet2sendFormat->getPacket());
    }

    enqueue(packet2sendFormat);

    pfDebug3(s_EnoceanLogChannel) << "<-Esp3PacketTransmitter::onSendRequest ";
}

void Esp3PacketTransmitter::enqueue(QspEsp3SentPacketFormat &packet2sendFormat)
{
    pfDebug8(s_EnoceanLogChannel) << "enqueue " << packet2sendFormat->logPacket();
    m_sendingRequestQueue.enqueue(packet2sendFormat);
}

QspEsp3SentPacketFormat Esp3PacketTransmitter::dequeue()
{
    QspEsp3SentPacketFormat lastSend{m_sendingRequestQueue.dequeue()};
    pfDebug8(s_EnoceanLogChannel) << "dequeue " << lastSend->logPacket();

    return lastSend;
}

void Esp3PacketTransmitter::startWatchDog()
{
    m_watchDog->start();
}

void Esp3PacketTransmitter::stopWatchDog()
{
    m_watchDog->stop();
}

void Esp3PacketTransmitter::sendHead()
{
    pfDebug3(s_EnoceanLogChannel) << "->Esp3PacketTransmitter::sendHead";

    pfDebug5(s_EnoceanLogChannel) << "Esp3PacketTransmitter::sendHead";

    if (!m_sendingRequestQueue.isEmpty())
    {
        QspEsp3SentPacketFormat packet2sendFormat{m_sendingRequestQueue.head()};
        emitPacket(packet2sendFormat->getPacket());
    }

    pfDebug3(s_EnoceanLogChannel) << "<-Esp3PacketTransmitter::sendHead";
}

void Esp3PacketTransmitter::emitPacket(QspEsp3Packet packet)
{
    pfInfo4(s_EnoceanMsgChannel) << "> " << packet->logPacket();
    emit sendPacket(packet);
    startWatchDog();
}

