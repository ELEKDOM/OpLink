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
#include "worker/workerargs.h"
#include "abstract_infrastructure/loading/confreadererror.h"
#include "abstract_infrastructure/loading/infrastructurestore.h"
#include "loader/enoceanconfreader.h"
#include "loader/enoceanusbgatewayargs.h"
#include "loader/enoceantcpgatewayargs.h"

using namespace elekdom::oplink::enocean;

EnoceanConfReader::EnoceanConfReader(const QString& logChannel,
                                     infrastructure::InfrastructureStore& store,
                                     worker::WorkerSignal *wSignal,
                                     const worker::QspWorkerArgs& args,
                                     QObject *parent):
    InfrastructureConfReader{logChannel,
                                      store,
                                      wSignal,
                                      args,
                                      parent}
{

}

EnoceanConfReader::~EnoceanConfReader()
{

}

void EnoceanConfReader::extractDataFromGateway(infrastructure::LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name() == usbStickNode())
        {

            QString baudrateAtt{m_xmlReader.attributes().value(baudrateAttribute()).toString()};
            QString dataBitsAtt{m_xmlReader.attributes().value(databitsAttribute()).toString()};
            QString stopBitsAtt{m_xmlReader.attributes().value(stopbitsAttribute()).toString()};
            QString parityAtt{m_xmlReader.attributes().value(parityAttribute()).toString()};
            QString dev{m_xmlReader.attributes().value(devAttribute()).toString()};

            pfInfo1(logChannel()) << "xml parser : baudeRate=" << baudrateAtt << ", dataBits=" << dataBitsAtt << ", stopBits=" << stopBitsAtt << ", parity=" << parityAtt << ", dev=" << dev;
            EnoceanUsbGatewayArgs gatewayArgs{baudrateAtt.toInt(),
                                              (QSerialPort::DataBits)dataBitsAtt.toInt(),
                                              (QSerialPort::StopBits)stopBitsAtt.toInt(),
                                              (QSerialPort::Parity)parityAtt.toInt(),
                                              dev};


            if (!m_store.addGateway(gatewayArgs))
            {
                err = infrastructure::LoadingError::StructuralError;
                pfWarning1(logChannel()) << QObject::tr("Echec de création de la passerelle USB EnOcean (baudrate %1 databits %2 stopbits %3 parity %4 dev %5)").arg(baudrateAtt,
                                                                                                                                                                  dataBitsAtt,
                                                                                                                                                                  stopBitsAtt,
                                                                                                                                                                  parityAtt,
                                                                                                                                                                  dev);
            }
        }
        else if (m_xmlReader.name() == tcpStickNode())
        {
            err = infrastructure::LoadingError::XmlError;
            pfErr(logChannel()) << QObject::tr("La passerelle EnOcean de type TCP n'est pas implémentée");
        }
        else
        {
            err = infrastructure::LoadingError::XmlError;
            pfErr(logChannel()) << QObject::tr("Il faut définir une passerelle EnOcean de type USB ou TCP");
        }
        if (infrastructure::LoadingError::NoError == err)
        {
            m_xmlReader.readNextStartElement(); // go back to gateway node
        }
    } // if (m_xmlReader.readNextStartElement())
    else
    {
        err = infrastructure::LoadingError::XmlError;
        pfWarning1(logChannel()) <<  QObject::tr("Les paramètres de la passerelle EnOcean ne sont pas définis");
    }
}
