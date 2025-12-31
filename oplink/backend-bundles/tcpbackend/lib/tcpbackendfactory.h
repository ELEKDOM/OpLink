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

#ifndef TCPBACKENDFACTORY_H
#define TCPBACKENDFACTORY_H

#include "abstract_network_tcp/server/tcpserverfactory.h"

class TcpBackendFactory : public plugframe::TcpServerFactory
{
public:
    TcpBackendFactory();
    ~TcpBackendFactory() override;

protected:
    plugframe::TcpChannelDeserializer *createDeserializer() override;
    plugframe::TcpServerChannelManager *createChannelManager(plugframe::TcpServer& bundle,
                                                             plugframe::TcpChannel *channel,
                                                             QObject *parent = nullptr) override;
};

#endif // TCPBACKENDFACTORY_H
