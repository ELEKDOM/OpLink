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

#include "tcpfrontenddeserializer.h"
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
#include "tcpfrontendlogchannel.h"

TcpFrontendDeserializer::TcpFrontendDeserializer() {}

TcpFrontendDeserializer::~TcpFrontendDeserializer()
{

}

plugframe::TcpChannelMessage *TcpFrontendDeserializer::deserialize(QDataStream &input)
{
    plugframe::TcpChannelMessage *ret{nullptr};
    quint16 msgType;

    // First, get message type
    input >> msgType;

    // Build the right message type
    // message types accepted as input from a server
    switch(msgType)
    {
    case static_cast<quint16>(oplink::MessageType::SiginReply) :
        ret = createSiginReplyMessage(input);
        break;

    case static_cast<quint16>(oplink::MessageType::Signout) :
        ret = createSignoutMessage(input);
        break;

    case static_cast<quint16>(oplink::MessageType::DownloadConfigReply) :
        ret = createDownloadConfigReplyMessage(input);
        break;

    case static_cast<quint16>(oplink::MessageType::SessionStarted) :
        ret = createSessionStartedMessage(input);
        break;

    case static_cast<quint16>(oplink::MessageType::StateValue) :
        ret = createStateValueMessage(input);
        break;

    default:
        pfErr(s_TcpFrontendLogChannel) << QObject::tr("Unknown input message type : ") << msgType;
    }

    return ret;
}

void TcpFrontendDeserializer::serialize(plugframe::TcpChannelMessage &msg, QDataStream &out)
{
    quint16 msgType{msg.msgType()};

    out << msg.msgType();

    switch(msgType)
    {
    case static_cast<quint16>(oplink::MessageType::Signin) :
        serializeSiginMessage(dynamic_cast<oplink::SigninMessage&>(msg),out);
        break;

    case static_cast<quint16>(oplink::MessageType::Signout) :
        serializeSignoutMessage(dynamic_cast<oplink::SignoutMessage&>(msg),out);
        break;

    case static_cast<quint16>(oplink::MessageType::DownloadConfig) :
        serializeDownloadConfigMessage(dynamic_cast<oplink::DownloadConfigMessage&>(msg),out);
        break;

    case static_cast<quint16>(oplink::MessageType::Ready) :
        serializeReadyMessage(dynamic_cast<oplink::ReadyMessage&>(msg),out);
        break;

    case static_cast<quint16>(oplink::MessageType::SubmitOrder) :
        serializeSubmitOrderMessage(dynamic_cast<oplink::SubmitOrderMessage&>(msg),out);
        break;

    default:
        pfErr(s_TcpFrontendLogChannel) << QObject::tr("Unknown output message type : ") << msgType;
    }
}

plugframe::TcpChannelMessage *TcpFrontendDeserializer::createSiginReplyMessage(QDataStream &input)
{
    quint32 sessionId;
    QString identifier;
    quint8 status;

    input >> sessionId >> identifier >> status;
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("< SiginReplyMessage : ") << sessionId << "," << identifier << "," << status;
    return new oplink::SigninReplyMessage(sessionId,
                                          identifier,
                                          static_cast<oplink::SigninReplyMessage::SigninStatus>(status));
}

plugframe::TcpChannelMessage *TcpFrontendDeserializer::createSignoutMessage(QDataStream &input)
{
    quint32 sessionId;

    input >> sessionId;
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("< SignoutMessage : ") << sessionId;
    return new oplink::SignoutMessage(sessionId);
}

plugframe::TcpChannelMessage *TcpFrontendDeserializer::createDownloadConfigReplyMessage(QDataStream &input)
{
    quint32 sessionId;
    QString xmlConfig;

    input >> sessionId >> xmlConfig;
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("< DownloadConfigReplyMessage : ") << sessionId << "," << xmlConfig;
    return new oplink::DownloadConfigReplyMessage(sessionId,xmlConfig);
}

plugframe::TcpChannelMessage *TcpFrontendDeserializer::createSessionStartedMessage(QDataStream &input)
{
    quint32 sessionId;
    quint16 confId;
    QString profil;

    input >> sessionId >> confId >> profil;
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("< SessionStartedMessage : ") << sessionId << "," << confId << "," << profil;
    return new oplink::SessionStartedMessage(sessionId,confId,profil);
}

plugframe::TcpChannelMessage *TcpFrontendDeserializer::createStateValueMessage(QDataStream &input)
{
    quint32 sessionId;
    QString observableName,propertyName;
    QVariant value;

    input >> sessionId >> observableName >> propertyName >> value;
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("< StateValueMessage : ") << sessionId << "," << observableName << "," << propertyName << "," << value;
    return new oplink::StateValueMessage(sessionId,observableName,propertyName,value);
}

void TcpFrontendDeserializer::serializeSiginMessage(oplink::SigninMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("> SigninMessage : ") << msg.frontendItf() << "," << msg.frontendIp() << "," << msg.identifier() << "," << msg.password();
    out << msg.frontendItf() << msg.frontendIp() << msg.identifier() << msg.password();
}

void TcpFrontendDeserializer::serializeSignoutMessage(oplink::SignoutMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("> SignoutMessage : ") << msg.sessionId();
    out << msg.sessionId();
}

void TcpFrontendDeserializer::serializeDownloadConfigMessage(oplink::DownloadConfigMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("> DownloadConfigMessage : ") << msg.sessionId();
    out << msg.sessionId();
}

void TcpFrontendDeserializer::serializeReadyMessage(oplink::ReadyMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("> ReadyMessage : ") << msg.sessionId();
    out << msg.sessionId();
}

void TcpFrontendDeserializer::serializeSubmitOrderMessage(oplink::SubmitOrderMessage &msg, QDataStream &out)
{
    pfInfo4(s_TcpFrontendLogChannel) << QObject::tr("> SubmitOrderMessage : ") << msg.sessionId() << "," << msg.order();
    out << msg.sessionId() << msg.order();
}
