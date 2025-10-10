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


#ifndef ENOCEANGATEWAY_H
#define ENOCEANGATEWAY_H

#include "abstract_infrastructure/area/areagateway.h"
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{
class EnoceanGateway : public core::infrastructure::AreaGateway
{
    Q_OBJECT

public:
    EnoceanGateway(const QString& logChannel,
                   EnoceanGatewayMode *mode,
                   QObject *parent = nullptr);
    ~ EnoceanGateway() override;

public:
    EnoceanGatewayMode *mode() {return m_mode.get();}
    virtual void buildGateway(EnoceanUsbGatewayArgs& gatewayArgs);
    virtual void buildGateway(EnoceanTcpGatewayArgs& gatewayArgs);
    void sendCommonCommand(QspCommonCommandFormat commonCommandFormat);
    void sendEepCommand(QspEepCommandFormat commandFormat);

public slots:
    void onPacketReceived(QspEsp3Packet packet);
    void onInitializeUsb300BaseId();

signals:
    void erp1PacketReceived(QspEepTelegramFormat erp1PacketFormat);

protected:
    virtual Esp3PacketTransmitter *createPacketTransmitter();
    virtual Esp3PacketSerialReceiver *createSerialPacketReceiver();
    virtual UsbGatewayPort *createSerialPort(EnoceanUsbGatewayArgs &gatewayArgs);

private:
    QspResponseFormat getExpectedResponseformat(const QspEsp3Packet& responsePacket);
    void initializeUsb300BaseId();

private slots:
    void onSendPacket(elekdom::oplink::enocean::QspEsp3Packet packet);

private:
    QspGatewayPort           m_port;
    QspEsp3PacketReceiver    m_packetReceiver;
    QspEsp3PacketTransmitter m_packetTransmitter;
    QspEnoceanGatewayMode    m_mode;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ENOCEANGATEWAY_H
