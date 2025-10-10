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


#ifndef SIGNINMESSAGE_H
#define SIGNINMESSAGE_H

#include <QString>
#include "message.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace tcp
{
class OLCORE_LIB_EXPORT SigninMessage : public Message
{
public:
    SigninMessage(QString frontendItf,
                  QString frontendIp,
                  QString identifier,
                  QString password);
    ~SigninMessage() override;

public:
    const QString& frontendItf() {return m_frontendItf;}
    const QString& frontendIp() {return m_frontendIp;}
    const QString& identifier() {return m_identifier;}
    const QString& password() {return m_password;}

private:
    QString m_frontendItf;
    QString m_frontendIp;
    QString m_identifier;
    QString m_password;
};
}//namespace tcp
}//namespace core
}//namespace oplink
}//namespace elekdom
#endif // SIGNINMESSAGE_H
