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


#include "tcpbackendfactory.h"
#include "tcpbackenddeserializer.h"
#include "tcpbackendchannelmanager.h"

using namespace elekdom::plugframe::core;
using namespace elekdom::oplink::tcpbackend::factory;
using namespace elekdom::oplink::tcpbackend::bundle;

TcpBackendFactory::TcpBackendFactory()
{

}

TcpBackendFactory::~TcpBackendFactory()
{

}

tcp::TcpChannelDeserializer *TcpBackendFactory::createDeserializer()
{
    return new TcpBackendDeserializer;
}

tcp::server::bundle::TcpServerChannelManager *TcpBackendFactory::createChannelManager(tcp::server::bundle::TcpServer &bundle,
                                                                                      tcp::TcpChannel *channel,
                                                                                      QObject *parent)
{
    return new TcpBackendChannelManager{bundle,channel,parent};
}
