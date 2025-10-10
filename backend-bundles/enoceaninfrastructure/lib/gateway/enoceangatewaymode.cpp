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
#include "gateway/enoceangatewaymode.h"
#include "enoceaninfrastructurelogchannel.h"
#include "packet/format/receivedformat/response/eepcommandresponseformat.h"
#include "packet/format/receivedformat/response/commoncommandresponse/readidbaseresponseformat.h"

using namespace elekdom::oplink::enocean;

EnoceanGatewayMode::EnoceanGatewayMode(QObject *parent):
    ResponseHandler{parent},
    m_usb300BaseId(0)
{

}

EnoceanGatewayMode::~EnoceanGatewayMode()
{

}

void EnoceanGatewayMode::visit(EepCommandResponseFormat &response)
{
    quint8 rc{response.returnCode()};
   // bool resend {rc != ResponseFormat::RET_OK};

    if (rc != ResponseFormat::RET_OK)
    {
        QString err;

        switch(rc)
        {
            case ResponseFormat::RET_ERROR:
                err = "ERROR";
                break;
            case ResponseFormat::RET_NOT_SUPPORTED:
                err = "NOT_SUPPORTED";
                break;
            case ResponseFormat::RET_WRONG_PARAM:
                err = "WRONG_PARAM";
                break;
            case ResponseFormat::RET_OPERATION_DENIED:
                err = "OPERATION_DENIED";
                break;
            case ResponseFormat::RET_LOCK_SET:
                err = "LOCK_SET";
                break;
            case ResponseFormat::RET_BUFFER_TO_SMALL:
                err = "BUFFER_TO_SMALL";
                break;
            case ResponseFormat::RET_NO_FREE_BUFFER:
                err = "NO_FREE_BUFFER";
        }

        pfInfo5(s_EnoceanLogChannel) << tr("Code d'erreur Enocean : %1").arg(err);
    }

    emit responseProcessed(false);
}

void EnoceanGatewayMode::visit(CommonCommandResponseFormat &response)
{
    Q_UNUSED(response)
}

void EnoceanGatewayMode::visit(ReadIdBaseResponseFormat &response)
{
    pfDebug3(s_EnoceanLogChannel) << "->EnoceanGatewayMode::visit ReadIdBaseResponseFormat";

    quint32 baseId;
    bool    resend{false};

    if (response.baseId(baseId))
    {
        m_usb300BaseId = baseId;
    }
    else
    {
        resend = true;
    }

    emit responseProcessed(resend);
    if (!resend)
    {
        emit usb300IdRecovered(); // to synchronize initial devices state
    }

    pfDebug3(s_EnoceanLogChannel) << "<-EnoceanGatewayMode::visit ReadIdBaseResponseFormat";
}
