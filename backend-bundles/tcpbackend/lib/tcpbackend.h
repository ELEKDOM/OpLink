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


#ifndef TCPBACKEND_H
#define TCPBACKEND_H

#include "abstract_network_tcp/server/tcpserver.h"
#include "service-int/loginserviceinterface.h"
#include "service-int/observableserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace tcpbackend
{
namespace bundle
{
class TcpBackend : public plugframe::core::tcp::server::bundle::TcpServer
{

public:
    TcpBackend();
    ~TcpBackend() override;

public:
    plugframe::users::service::LoginServiceInterface *loginService();
    engine::service::ObservableServiceInterface *observableService();

protected:
    plugframe::core::bundle::BundleFactory* createFactory() override;
};

} //namespace bundle
} //namespace tcpbackend
} //namespace oplink
} //namespace elekdom

#endif // TCPBACKEND_H
