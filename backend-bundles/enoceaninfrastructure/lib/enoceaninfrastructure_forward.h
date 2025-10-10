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


#ifndef ENOCEANINFRASTRUCTURE_FORWARD_H
#define ENOCEANINFRASTRUCTURE_FORWARD_H

#include <QSharedPointer>

namespace elekdom
{
namespace oplink
{
namespace enocean
{
    class EepCommandFormat;
    class EepCommandFormat;
    class EepTelegramFormat;
    class EnoceanGateway;
    class Esp3Packet;
    class GatewayPort;
    class Esp3PacketReceiver;
    class Esp3PacketTransmitter;
    class EnoceanGatewayMode;
    class EnoceanTcpGatewayArgs;
    class EnoceanUsbGatewayArgs;
    class CommonCommandFormat;
    class Esp3PacketSerialReceiver;
    class UsbGatewayPort;
    class ResponseFormat;
    class Esp3SentPacketFormat;
    class EepCommandResponseFormat;
    class CommonCommandResponseFormat;
    class ReadIdBaseResponseFormat;
    class D201StatusQuery;
    class D201SetOutput;
    class D201PilotWireModeQuery;
    class D201SetPilotWireMode;
    class D201MeasurementEnergyQuery;
    class D201MeasurementPowerQuery;
    class ResponseHandler;
    class D2CommandProcessor;
    class D201CommandProcessor;
    class D20112CommandProcessor;
    class EnoceanCommandProcessor;
    class EnoceanEquipmentProfile;
    class D201TelegramFormat;
    class F601TelegramFormat;
    class F602TelegramFormat;
    class A504TelegramFormat;
    class D500TelegramFormat;
    class Esp3ReceivedPacketFormat;
    class ReadIdBaseFormat;
    class D2CommandFormat;
    class D201Cmd1Format;
    class D201Cmd3Format;
    class D201Cmd6Format;
    class D201Cmd8Format;
    class D201Cmd9Format;
    class D201CommandFormat;
    class Esp3PacketFormat;

    using QspEepTelegramFormat = QSharedPointer<EepTelegramFormat>;
    using QspD2CommandProcessor  = QSharedPointer<D2CommandProcessor>;
    using QspD201CommandProcessor  = QSharedPointer<D201CommandProcessor>;
    using QspD20112CommandProcessor  = QSharedPointer<D20112CommandProcessor>;
    using QspD20112SetOutput  = QSharedPointer<D201SetOutput>;
    using QspD20112StatusQuery  = QSharedPointer<D201StatusQuery>;
    using QspEepCommandFormat = QSharedPointer<EepCommandFormat>;
    using QspEnoceanCommandProcessor  = QSharedPointer<EnoceanCommandProcessor>;
    using QspEsp3Packet = QSharedPointer<Esp3Packet>;
    using QspEnoceanEquipmentProfile  = QSharedPointer<EnoceanEquipmentProfile>;
    using QspCommonCommandFormat = QSharedPointer<CommonCommandFormat>;
    using QspResponseFormat = QSharedPointer<ResponseFormat>;
    using QspGatewayPort = QSharedPointer<GatewayPort>;
    using QspEsp3PacketReceiver = QSharedPointer<Esp3PacketReceiver>;
    using QspEsp3PacketTransmitter = QSharedPointer<Esp3PacketTransmitter>;
    using QspEnoceanGatewayMode = QSharedPointer<EnoceanGatewayMode>;
    using QspEsp3SentPacketFormat = QSharedPointer<Esp3SentPacketFormat>;
    using QspD201TelegramFormat = QSharedPointer<D201TelegramFormat>;
    using QspF601TelegramFormat = QSharedPointer<F601TelegramFormat>;
    using QspF602TelegramFormat = QSharedPointer<F602TelegramFormat>;
    using QspA504TelegramFormat = QSharedPointer<A504TelegramFormat>;
    using QspD500TelegramFormat = QSharedPointer<D500TelegramFormat>;
    using QspCommonCommandResponseFormat = QSharedPointer<CommonCommandResponseFormat>;
    using QspReadIdBaseResponseFormat = QSharedPointer<ReadIdBaseResponseFormat>;
    using QspRadioTelegramResponseFormat = QSharedPointer<EepCommandResponseFormat>;
    using QspEsp3ReceivedPacketFormat = QSharedPointer<Esp3ReceivedPacketFormat>;
    using QspReadIdBaseFormat = QSharedPointer<ReadIdBaseFormat>;
    using QspD2CommandFormat = QSharedPointer<D2CommandFormat>;
    using QspD201Cmd1Format = QSharedPointer<D201Cmd1Format>;
    using QspD201Cmd3Format = QSharedPointer<D201Cmd3Format>;
    using QspD201Cmd6Format = QSharedPointer<D201Cmd6Format>;
    using QspD201Cmd8Format = QSharedPointer<D201Cmd8Format>;
    using QspD201Cmd9Format = QSharedPointer<D201Cmd9Format>;
    using QspD201CommandFormat = QSharedPointer<D201CommandFormat>;
    using QspEsp3PacketFormat = QSharedPointer<Esp3PacketFormat>;

}//namespace enocean
}//namespace oplink
}//namespace elekdom
#endif // ENOCEANINFRASTRUCTURE_FORWARD_H
