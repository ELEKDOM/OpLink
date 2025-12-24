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

#include "loader/enoceanusbgatewayargs.h"
#include "gateway/enoceangateway.h"

EnoceanUsbGatewayArgs::EnoceanUsbGatewayArgs(qint32 baudRate,
                                             QSerialPort::DataBits dataBits,
                                             QSerialPort::StopBits stopBits,
                                             QSerialPort::Parity parity,
                                             QString dev):
    m_baudRate{baudRate},
    m_dataBits{dataBits},
    m_stopBits{stopBits},
    m_parity{parity},
    m_dev{dev}
{

}

EnoceanUsbGatewayArgs::~EnoceanUsbGatewayArgs()
{

}

void EnoceanUsbGatewayArgs::accept(EnoceanGateway &argsVisitor)
{
    argsVisitor.buildGateway(*this);
}
