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

#include "bundle/bundlecontext.h"
#include "tcpbackend.h"
#include "tcpbackendfactory.h"
#include "tcpbackendlogchannel.h"

TcpBackend::TcpBackend():
    plugframe::TcpServer{s_TcpBackendLogChannel}
{

}

TcpBackend::~TcpBackend()
{

}

plugframe::LoginServiceInterface *TcpBackend::loginService()
{
    plugframe::LoginServiceInterface *ret;

    ret = bundleContext()->getService<plugframe::LoginServiceInterface>(plugframe::LoginServiceInterface::serviceName());
    return ret;
}

oplink::ObservableServiceInterface *TcpBackend::observableService()
{
    oplink::ObservableServiceInterface *ret;

    ret = bundleContext()->getService<oplink::ObservableServiceInterface>(oplink::ObservableServiceInterface::serviceName());
    return ret;
}

plugframe::BundleFactory *TcpBackend::createFactory()
{
    return new TcpBackendFactory;
}

