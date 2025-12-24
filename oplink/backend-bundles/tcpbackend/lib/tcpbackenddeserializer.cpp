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

#include "tcpbackenddeserializer.h"
#include "tcpbackendlogchannel.h"
#include "network_tcp/messagetype.h"
#include "network_tcp/signinmessage.h"
#include "network_tcp/signinreplymessage.h"
#include "network_tcp/sessionstartedmessage.h"
#include "network_tcp/signoutmessage.h"
#include "network_tcp/downloadconfigmessage.h"
#include "network_tcp/readymessage.h"
#include "network_tcp/downloadconfigreplymessage.h"
#include "network_tcp/submitordermessage.h"
#include "network_tcp/statevaluemessage.h"
#include "logger/pflog.h"

TcpBackendDeserializer::TcpBackendDeserializer()
{

}

TcpBackendDeserializer::~TcpBackendDeserializer()
{

}

///
/// \brief TcpBackendDeserializer::deserialize
/// \param input
/// \return input message
///
plugframe::TcpChannelMessage *TcpBackendDeserializer::deserialize(QDataStream &input)
{
    plugframe::TcpChannelMessage *ret{nullptr};
    quint16 msgType;

    // First, get message type
    input >> msgType;

    // Build the right message type
    // message types accepted as input from a client
    switch(msgType)
    {
    case static_cast<quint16>(oplink::MessageType::Signin) :
            ret = createSiginMessage(input);
        break;

        case static_cast<quint16>(oplink::MessageType::Signout) :
            ret = createSignoutMessage(input);
        break;

        case static_cast<quint16>(oplink::MessageType::DownloadConfig) :
            ret = createDownloadConfigMessage(input);
        break;

        case static_cast<quint16>(oplink::MessageType::Ready) :
            ret = createReadyMessage(input);
            break;

        case static_cast<quint16>(oplink::MessageType::SubmitOrder) :
            ret = createSubmitOrderMessage(input);
        break;

        default:
            pfErr(s_TcpBackendLogChannel) << QObject::tr("Unknown input message type : ") << msgType;
    }

    return ret;
}

///
/// \brief TcpBackendDeserializer::serialize
///        transforms a message to be sent into an output stream
/// \param msg
/// \param out
///
void TcpBackendDeserializer::serialize(plugframe::TcpChannelMessage &msg, QDataStream &out)
{
    quint16 msgType{msg.msgType()};

    out << msg.msgType();

    switch(msgType)
    {
        case static_cast<quint16>(oplink::MessageType::SiginReply) :
            serializeSiginReplyMessage(dynamic_cast<oplink::SigninReplyMessage&>(msg),out);
        break;

        case static_cast<quint16>(oplink::MessageType::Signout) :
            serializeSignoutMessage(dynamic_cast<oplink::SignoutMessage&>(msg),out);
        break;

        case static_cast<quint16>(oplink::MessageType::DownloadConfigReply) :
            serializeDownloadConfigReplyMessage(dynamic_cast<oplink::DownloadConfigReplyMessage&>(msg),out);
        break;

        case static_cast<quint16>(oplink::MessageType::SessionStarted) :
            serializeSessionStartedMessage(dynamic_cast<oplink::SessionStartedMessage&>(msg),out);
        break;

        case static_cast<quint16>(oplink::MessageType::StateValue) :
            serializeStateValueMessage(dynamic_cast<oplink::StateValueMessage&>(msg),out);
            break;

    default:
        pfErr(s_TcpBackendLogChannel) << QObject::tr("Unknown output message type : ") << msgType;
    }
}

plugframe::TcpChannelMessage *TcpBackendDeserializer::createSiginMessage(QDataStream &input)
{
    QString frontendItf,frontendIp,identifier,password;

    input >> frontendItf >> frontendIp >> identifier >> password;
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("< SiginMessage : ") << frontendItf << "," << frontendIp << "," << identifier << "," << password;
    return new oplink::SigninMessage(frontendItf,frontendIp,identifier,password);
}

plugframe::TcpChannelMessage *TcpBackendDeserializer::createSignoutMessage(QDataStream &input)
{
    quint32 sessionId;

    input >> sessionId;
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("< SignoutMessage : ") << sessionId;
    return new oplink::SignoutMessage(sessionId);
}

plugframe::TcpChannelMessage *TcpBackendDeserializer::createDownloadConfigMessage(QDataStream &input)
{
    quint32 sessionId;

    input >> sessionId;
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("< DownloadConfigMessage : ") << sessionId;
    return new oplink::DownloadConfigMessage(sessionId);
}

plugframe::TcpChannelMessage *TcpBackendDeserializer::createReadyMessage(QDataStream &input)
{
    quint32 sessionId;

    input >> sessionId;
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("< ReadyMessage : ") << sessionId;
    return new oplink::ReadyMessage(sessionId);
}

plugframe::TcpChannelMessage *TcpBackendDeserializer::createSubmitOrderMessage(QDataStream &input)
{
    quint32 sessionId;
    QString order;

    input >> sessionId >> order;
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("< SubmitOrderMessage : ") << sessionId << "," << order;
    return new oplink::SubmitOrderMessage(sessionId,order);
}

void TcpBackendDeserializer::serializeSiginReplyMessage(oplink::SigninReplyMessage &msg, QDataStream &out)
{
    quint8 status{static_cast<quint8>(msg.status())};

    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("> SiginReplyMessage : ") << msg.sessionId() << "," << msg.identifier() << "," << status;
    out << msg.sessionId() << msg.identifier() << status;
}

void TcpBackendDeserializer::serializeSignoutMessage(oplink::SignoutMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("> SignoutMessage : ") << msg.sessionId();
    out << msg.sessionId();
}

void TcpBackendDeserializer::serializeDownloadConfigReplyMessage(oplink::DownloadConfigReplyMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("> DownloadConfigReplyMessage : ") << msg.sessionId() << "," << msg.xmlConfig();
    out << msg.sessionId() << msg.xmlConfig();
}

void TcpBackendDeserializer::serializeSessionStartedMessage(oplink::SessionStartedMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("> SessionStartedMessage : ") << msg.sessionId() << "," << msg.confId() << "," << msg.profile();
    out << msg.sessionId() << msg.confId() << msg.profile();
}

void TcpBackendDeserializer::serializeStateValueMessage(oplink::StateValueMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpBackendLogChannel) << QObject::tr("> StateValueMessage : ") << msg.sessionId() << "," << msg.observableName() << "," << msg.propertyName() << "," << msg.value();
    out << msg.sessionId() << msg.observableName() << msg.propertyName() << msg.value();
}
