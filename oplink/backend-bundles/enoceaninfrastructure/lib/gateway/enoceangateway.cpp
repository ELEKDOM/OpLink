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

#include <QByteArray>
#include "enoceangateway.h"
#include "logger/pflog.h"
#include "enoceaninfrastructurelogchannel.h"
#include "gateway/esp3packetserialreceiver.h"
#include "gateway/esp3packettransmitter.h"
#include "loader/enoceanusbgatewayargs.h"
#include "loader/enoceantcpgatewayargs.h"
#include "packet/format/sentformat/commoncommand/readidbaseformat.h"
#include "packet/format/sentformat/eepcommandformat/eepcommandformat.h"
#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"
#include "packet/format/receivedformat/response/responseformat.h"
#include "packet/esp3packet.h"

EnoceanGateway::EnoceanGateway(const QString& logChannel,
                               EnoceanGatewayMode *mode,
                               QObject *parent):
    AreaGateway{logChannel, parent},
    m_mode{mode}
{
    m_mode->setParent(this);
}

EnoceanGateway::~EnoceanGateway()
{
    m_port->close();
}

void EnoceanGateway::buildGateway(EnoceanUsbGatewayArgs &gatewayArgs)
{
    Esp3PacketTransmitter *packeTransmitter{createPacketTransmitter()};
    Esp3PacketSerialReceiver *packetReceiver{createSerialPacketReceiver()};
    UsbGatewayPort *usbPort{createSerialPort(gatewayArgs)};

    packeTransmitter->setParent(this);
    packetReceiver->setParent(this);
    usbPort->setParent(this);

    bool ok = connect(usbPort, SIGNAL(byteReceived(quint8)), packetReceiver, SLOT(input(quint8)));
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanGateway connect signal byteReceived : échec");
    }

    ok = connect(packetReceiver, SIGNAL(packetReceived(QspEsp3Packet)), SLOT(onPacketReceived(QspEsp3Packet)));
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanGateway connect signal packetReceived : échec");
    }

    ok = connect(m_mode.get(), SIGNAL(responseProcessed(bool)), packeTransmitter, SLOT(onResponseProcessed(bool)));
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanGateway connect signal responseProcessed : échec");
    }

    ok = connect(packeTransmitter,
                 SIGNAL(sendPacket(elekdom::oplink::enocean::QspEsp3Packet)),
                 SLOT(onSendPacket(elekdom::oplink::enocean::QspEsp3Packet)),
                 Qt::QueuedConnection);
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanGateway connect signal sendPacket : échec");
    }

    m_packetTransmitter.reset(packeTransmitter);
    m_packetReceiver.reset(packetReceiver);
    m_port.reset(usbPort);
}

void EnoceanGateway::buildGateway(EnoceanTcpGatewayArgs &gatewayArgs)
{
    Q_UNUSED(gatewayArgs)
    // TODO
    //...
}

void EnoceanGateway::sendCommonCommand(QspCommonCommandFormat commonCommandFormat)
{
    m_packetTransmitter->sendPaquetRequest(commonCommandFormat);
}

void EnoceanGateway::sendEepCommand(QspEepCommandFormat commandFormat)
{
    quint32 baseId{m_mode->usb300BaseId()};

    if (!baseId)
    {
        pfWarning1(logChannel()) << tr("La passerelle EnOcean envoie un message avec un id d'émetteur à 0 !");
    }

    commandFormat->insertSenderId(baseId);
    m_packetTransmitter->sendPaquetRequest(commandFormat);
}

void EnoceanGateway::onPacketReceived(QspEsp3Packet packet)
{
    pfDebug3(logChannel()) << "->EnoceanGateway::onPacketReceived";

    if (packet->packetType() == Esp3Packet::RADIO_ERP1)
    {
        pfDebug4(logChannel()) << "EnoceanGateway::onPacketReceived RADIO_ERP1";

        QspEepTelegramFormat erp1Format{new EepTelegramFormat(packet)};

        if (erp1Format->getSenderId().toUInt(nullptr, 16) != m_mode->usb300BaseId())
        {
            emit erp1PacketReceived(erp1Format);
        }
        else
        {
            pfDebug6(logChannel()) << packet->logPacket() << " Filtré!";
        }
    }
    else if (packet->packetType() == Esp3Packet::RESPONSE)
    {
        pfDebug4(logChannel()) << "EnoceanGateway::onPacketReceived RESPONSE";

        QspResponseFormat responsePacketFormat{getExpectedResponseformat(packet)}; // format of the expected response of the last message sent

        if (!responsePacketFormat.isNull())
        {
            responsePacketFormat->accept(*m_mode);
        }
    }
    else
    {
        pfWarning7(logChannel()) << tr("Gateway : type de paquet non géré, 0x") << Qt::hex << packet->packetType();
    }

    pfDebug3(logChannel()) << "<-EnoceanGateway::onPacketReceived";
}

void EnoceanGateway::onInitializeUsb300BaseId()
{
    initializeUsb300BaseId();
}

Esp3PacketTransmitter *EnoceanGateway::createPacketTransmitter()
{
    return new Esp3PacketTransmitter;
}

Esp3PacketSerialReceiver *EnoceanGateway::createSerialPacketReceiver()
{
    return new Esp3PacketSerialReceiver;
}

UsbGatewayPort *EnoceanGateway::createSerialPort(EnoceanUsbGatewayArgs &gatewayArgs)
{
    return new UsbGatewayPort{gatewayArgs.m_baudRate,
                              gatewayArgs.m_dataBits,
                              gatewayArgs.m_stopBits,
                              gatewayArgs.m_parity,
                              gatewayArgs.m_dev};
}

QspResponseFormat EnoceanGateway::getExpectedResponseformat(const QspEsp3Packet& responsePacket)
{
    return m_packetTransmitter->getExpectedResponseformat(responsePacket);
}

void EnoceanGateway::initializeUsb300BaseId()
{
    QspReadIdBaseFormat readIdFormat{new ReadIdBaseFormat};

    // create and fill in command
    readIdFormat->newPacket();

    // send command to stick
    sendCommonCommand(readIdFormat);
}

void EnoceanGateway::onSendPacket(QspEsp3Packet packet)
{
    pfDebug5(logChannel()) << "USB Gateway send " << packet->logPacket();
    m_port->write(packet->dataFrame());
}

