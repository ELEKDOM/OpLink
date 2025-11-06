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

#ifndef USBGATEWAYPORT_H
#define USBGATEWAYPORT_H

#include <QSerialPort>
#include "gatewayport.h"

class UsbGatewayPort : public GatewayPort
{
    Q_OBJECT

public:
    UsbGatewayPort(const qint32 baudRate,
                   const QSerialPort::DataBits dataBits,
                   const QSerialPort::StopBits stopBits,
                   const QSerialPort::Parity parity,
                   const QString& name);
    ~UsbGatewayPort() override;

signals:
    void byteReceived(quint8 byte);

protected:
    bool open() override;
    void close() override;
    void write(QByteArray data) override;

private slots:
    void readData();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort                  m_serialPort;
    QSerialPort::SerialPortError m_lastError;
};
#endif // USBGATEWAYPORT_H
