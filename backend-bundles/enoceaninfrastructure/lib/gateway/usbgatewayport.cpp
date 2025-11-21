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

#include "logger/pflog.h"
#include "gateway/usbgatewayport.h"
#include "enoceaninfrastructurelogchannel.h"

UsbGatewayPort::UsbGatewayPort(const qint32 baudRate,
                               const QSerialPort::DataBits dataBits,
                               const QSerialPort::StopBits stopBits,
                               const QSerialPort::Parity parity,
                               const QString &name):
    m_lastError{QSerialPort::SerialPortError::NoError}
{
    m_serialPort.setBaudRate(baudRate);
    m_serialPort.setDataBits(dataBits);
    m_serialPort.setStopBits(stopBits);
    m_serialPort.setParity(parity);
    m_serialPort.setPortName(name);
    m_serialPort.setParent(this);

    bool ret = connect(&m_serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onErrorOccurred(QSerialPort::SerialPortError)));
    if (!ret)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--UsbGatewayPort connect signal errorOccurred : échec");
    }

    ret = connect(&m_serialPort, SIGNAL(readyRead()), SLOT(readData()));
    if (!ret)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--UsbGatewayPort connect signal readyRead : échec");
    }

    // Caution
    // For QSerialPort, open must be done in the main thread !
    // See Qt documentation

    m_serialPort.open(QIODevice::ReadWrite);
    ret = m_serialPort.isOpen();
    if (!ret)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--UsbGatewayPort ouverture port série : échec");
        m_serialPort.clearError();
    }

}

UsbGatewayPort::~UsbGatewayPort()
{
}

bool UsbGatewayPort::open()
{
   // Caution
   // For QSerialPort, open must be done in the main thread !
   // See Qt ocumentation

   return true;
}

void UsbGatewayPort::close()
{
    m_serialPort.close();
}

void UsbGatewayPort::write(QByteArray data)
{
    m_serialPort.write(data);
}

void UsbGatewayPort::readData()
{
    if (m_serialPort.bytesAvailable())
    {
        QByteArray data {m_serialPort.readAll()};

        pfInfo2(s_EnoceanMsgChannel) << tr("USB < ") << data.toHex(':');
        for (int i = 0; i < data.size(); i++)
        {

            emit byteReceived(data[i]);
        }
    }
}

void UsbGatewayPort::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::SerialPortError::NoError && error != m_lastError)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("Erreur du port série. Erreur = ") << error;
        m_lastError = error;
        m_serialPort.clearError();
    }
}
