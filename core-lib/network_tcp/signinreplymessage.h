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

#ifndef SIGNINREPLYMESSAGE_H
#define SIGNINREPLYMESSAGE_H

#include <QString>
#include "sessionmessage.h"

namespace oplink
{
class OLCORE_LIB_EXPORT SigninReplyMessage : public SessionMessage
{
public:
    enum class SigninStatus : quint8 {Ok,
                                      PasswordErr,
                                      IdentifierErr,
                                      InternalErr};

public:
    SigninReplyMessage(quint32 sessionId,QString identifier,SigninStatus status);
    ~SigninReplyMessage() override;

public:
    const QString& identifier() {return m_identifier;}
    SigninStatus status() {return m_status;}

private:
    QString      m_identifier;
    SigninStatus m_status;
};
}//namespace oplink
#endif // SIGNINREPLYMESSAGE_H
