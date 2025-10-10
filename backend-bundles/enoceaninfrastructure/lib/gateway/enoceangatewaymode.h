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


#ifndef ENOCEANGATEWAYMODE_H
#define ENOCEANGATEWAYMODE_H

#include <QSharedPointer>
#include "gateway/responsehandler.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{
class EnoceanGatewayMode : public ResponseHandler
{
    Q_OBJECT

public:
    EnoceanGatewayMode(QObject *parent = nullptr);
    ~EnoceanGatewayMode() override;

public:
    quint32 usb300BaseId() {return m_usb300BaseId;}

signals:
    void usb300IdRecovered();

protected:
    void visit(EepCommandResponseFormat& response) override;
    void visit(CommonCommandResponseFormat& response) override;
    void visit(ReadIdBaseResponseFormat& response) override;

private:
    quint32 m_usb300BaseId;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ENOCEANGATEWAYMODE_H
