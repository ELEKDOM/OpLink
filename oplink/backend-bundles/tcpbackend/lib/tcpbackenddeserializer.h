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

#ifndef TCPBACKENDDESERIALIZER_H
#define TCPBACKENDDESERIALIZER_H

#include "abstract_network_tcp/common/tcpchanneldeserializer.h"
#include "olcore-lib_forward.h"

class TcpBackendDeserializer : public plugframe::TcpChannelDeserializer
{
public:
    TcpBackendDeserializer();
    ~TcpBackendDeserializer() override;

protected:
    plugframe::TcpChannelMessage *deserialize(QDataStream& input) override;
    void serialize(plugframe::TcpChannelMessage& msg,QDataStream& out) override;

    // input msgs
    virtual plugframe::TcpChannelMessage *createSiginMessage(QDataStream &input);
    virtual plugframe::TcpChannelMessage *createSignoutMessage(QDataStream &input);
    virtual plugframe::TcpChannelMessage *createDownloadConfigMessage(QDataStream &input);
    virtual plugframe::TcpChannelMessage *createReadyMessage(QDataStream &input);
    virtual plugframe::TcpChannelMessage *createSubmitOrderMessage(QDataStream &input);

    // output msgs
    virtual void serializeSiginReplyMessage(oplink::SigninReplyMessage& msg,QDataStream& out);
    virtual void serializeSignoutMessage(oplink::SignoutMessage& msg,QDataStream& out);
    virtual void serializeDownloadConfigReplyMessage(oplink::DownloadConfigReplyMessage& msg,QDataStream& out);
    virtual void serializeSessionStartedMessage(oplink::SessionStartedMessage& msg,QDataStream& out);
    virtual void serializeStateValueMessage(oplink::StateValueMessage& msg,QDataStream& out);
};

#endif // TCPBACKENDDESERIALIZER_H
