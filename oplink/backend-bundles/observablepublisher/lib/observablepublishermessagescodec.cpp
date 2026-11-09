// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
//
// This file is part of PlugFrame.
//
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//
#include "observablepublishermessagescodec.h"
#include "observablepublisher_logchannel.h"
#include "network/channel/codectype.h"
#include "network/channel/messagetype.h"
#include "logger/pflog.h"

ObservablePublisherMessagesCodec::ObservablePublisherMessagesCodec(QObject *parent):
    plugframe::MessagesCodec{static_cast<quint16>(oplink::CodecType::ObservableSupervision),s_ObservablePublisher_LogChannel,parent}
{

}

bool ObservablePublisherMessagesCodec::extractArgsFromStream(quint16 msgId, QDataStream &input)
{
    bool ret{false};

    switch(msgId)
    {
        case static_cast<quint16>(oplink::MessageType::Signin) :
            ret = extractSiginMessage(input);
            break;

        case static_cast<quint16>(oplink::MessageType::Signout) :
            ret = extractSignoutMessage(input);
            break;

        case static_cast<quint16>(oplink::MessageType::DownloadConfig) :
            ret = extractDownloadConfigMessage(input);
            break;

        case static_cast<quint16>(oplink::MessageType::Ready) :
            ret = extractReadyMessage(input);
            break;

        case static_cast<quint16>(oplink::MessageType::SubmitOrder) :
            ret = extractSubmitOrderMessage(input);
            break;

        default:
            pfErr(logChannel()) << tr("Unknown input message type : ") << msgId;
    }

    return ret;
}

bool ObservablePublisherMessagesCodec::extractSiginMessage(QDataStream &input)
{
    QString frontendItf,frontendIp,identifier,password;

    input >> frontendItf >> frontendIp >> identifier >> password;
    pfInfo4(logChannel()) << tr("< SiginMessage : ") << frontendItf << "," << frontendIp << "," << identifier << "," << password;
    emit signinMessage(frontendItf,frontendIp,identifier,password);
    return true;
}

bool ObservablePublisherMessagesCodec::extractSignoutMessage(QDataStream &input)
{
    quint32 sessionId;

    input >> sessionId;
    pfInfo4(logChannel()) << tr("< SignoutMessage : ") << sessionId;
    emit signoutMessage(sessionId);
    return true;
}

bool ObservablePublisherMessagesCodec::extractDownloadConfigMessage(QDataStream &input)
{
    quint32 sessionId;

    input >> sessionId;
    pfInfo4(logChannel()) << tr("< DownloadConfigMessage : ") << sessionId;
    emit downloadConfigMessage(sessionId);
    return true;
}

bool ObservablePublisherMessagesCodec::extractReadyMessage(QDataStream &input)
{
   quint32 sessionId;

    input >> sessionId;
    pfInfo4(logChannel()) << tr("< ReadyMessage : ") << sessionId;
    emit readyMessage(sessionId);
    return true;
}

bool ObservablePublisherMessagesCodec::extractSubmitOrderMessage(QDataStream &input)
{
    quint32 sessionId;
    QString order;

    input >> sessionId >> order;
    pfInfo4(logChannel()) << tr("< SubmitOrderMessage : ") << sessionId << "," << order;
    emit submitOrderMessage(sessionId,order);
    return true;
}
