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


#ifndef SUBMITORDERMESSAGE_H
#define SUBMITORDERMESSAGE_H

#include <QString>
#include "sessionmessage.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace tcp
{
class OLCORE_LIB_EXPORT SubmitOrderMessage : public SessionMessage
{
public:
    SubmitOrderMessage(quint32 sessionId,QString order);
    ~SubmitOrderMessage() override;

    const QString& order() {return m_order;}

private:
    QString m_order;
};
}//namespace tcp
}//namespace core
}//namespace oplink
}//namespace elekdom
#endif // SUBMITORDERMESSAGE_H
