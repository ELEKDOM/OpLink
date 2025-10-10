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


#ifndef TCPFRONTENDDESERIALIZER_H
#define TCPFRONTENDDESERIALIZER_H

#include "abstract_network_tcp/common/tcpchanneldeserializer.h"
#include "olcore-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace tcpfrontend
{
namespace bundle
{

class TcpFrontendDeserializer : public plugframe::core::tcp::TcpChannelDeserializer
{
public:
    TcpFrontendDeserializer();
    ~TcpFrontendDeserializer() override;

protected:
    plugframe::core::tcp::TcpChannelMessage *deserialize(QDataStream& input) override;
    virtual void serialize(plugframe::core::tcp::TcpChannelMessage& msg, QDataStream& out) override;

    // input msgs
    virtual plugframe::core::tcp::TcpChannelMessage *createSiginReplyMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createSignoutMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createDownloadConfigReplyMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createSessionStartedMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createStateValueMessage(QDataStream &input);

    // output msgs
    virtual void serializeSiginMessage(core::tcp::SigninMessage& msg,QDataStream& out);
    virtual void serializeSignoutMessage(core::tcp::SignoutMessage& msg,QDataStream& out);
    virtual void serializeDownloadConfigMessage(core::tcp::DownloadConfigMessage& msg,QDataStream& out);
    virtual void serializeReadyMessage(core::tcp::ReadyMessage& msg,QDataStream& out);
    virtual void serializeSubmitOrderMessage(core::tcp::SubmitOrderMessage& msg,QDataStream& out);
};

} //namespace bundle
} //namespace tcpfrontend
} //namespace oplink
} //namespace elekdom

#endif // TCPFRONTENDDESERIALIZER_H
