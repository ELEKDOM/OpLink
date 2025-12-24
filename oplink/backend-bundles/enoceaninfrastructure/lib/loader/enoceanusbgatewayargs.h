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

#ifndef ENOCEANUSBGATEWAYARGS_H
#define ENOCEANUSBGATEWAYARGS_H

#include <QtSerialPort/QSerialPort>
#include "enoceangatewayargs.h"

class EnoceanUsbGatewayArgs : public EnoceanGatewayArgs
{
public:
    EnoceanUsbGatewayArgs(qint32 baudRate,
                          QSerialPort::DataBits dataBits,
                          QSerialPort::StopBits stopBits,
                          QSerialPort::Parity   parity,
                          QString               dev);
    ~EnoceanUsbGatewayArgs() override;

protected:
    void accept(EnoceanGateway& argsVisitor) override;

public:
    qint32                m_baudRate;
    QSerialPort::DataBits m_dataBits;
    QSerialPort::StopBits m_stopBits;
    QSerialPort::Parity   m_parity;
    QString               m_dev;
};
#endif // ENOCEANUSBGATEWAYARGS_H
