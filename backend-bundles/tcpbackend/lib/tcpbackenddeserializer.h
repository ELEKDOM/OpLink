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

namespace elekdom
{
namespace oplink
{
namespace tcpbackend
{
namespace bundle
{

class TcpBackendDeserializer : public plugframe::core::tcp::TcpChannelDeserializer
{
public:
    TcpBackendDeserializer();
    ~TcpBackendDeserializer() override;

protected:
    plugframe::core::tcp::TcpChannelMessage *deserialize(QDataStream& input) override;
    void serialize(plugframe::core::tcp::TcpChannelMessage& msg,QDataStream& out) override;

    // input msgs
    virtual plugframe::core::tcp::TcpChannelMessage *createSiginMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createSignoutMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createDownloadConfigMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createReadyMessage(QDataStream &input);
    virtual plugframe::core::tcp::TcpChannelMessage *createSubmitOrderMessage(QDataStream &input);

    // output msgs
    virtual void serializeSiginReplyMessage(core::tcp::SigninReplyMessage& msg,QDataStream& out);
    virtual void serializeSignoutMessage(core::tcp::SignoutMessage& msg,QDataStream& out);
    virtual void serializeDownloadConfigReplyMessage(core::tcp::DownloadConfigReplyMessage& msg,QDataStream& out);
    virtual void serializeSessionStartedMessage(core::tcp::SessionStartedMessage& msg,QDataStream& out);
    virtual void serializeStateValueMessage(core::tcp::StateValueMessage& msg,QDataStream& out);
};

} //namespace bundle
} //namespace tcpbackend
} //namespace oplink
} //namespace elekdom

#endif // TCPBACKENDDESERIALIZER_H
