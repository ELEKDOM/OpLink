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


#ifndef STATEVALUEMESSAGE_H
#define STATEVALUEMESSAGE_H

#include <QString>
#include <QVariant>
#include "sessionmessage.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace tcp
{
class OLCORE_LIB_EXPORT StateValueMessage : public SessionMessage
{
public:
    StateValueMessage(quint32 sessionId,QString observableName,QString propertyName,QVariant value);
    ~StateValueMessage() override;

public:
    const QString& observableName() {return m_observableName;}
    const QString& propertyName() {return m_propertyName;}
    const QVariant& value() {return m_value;}

private:
    QString  m_observableName;
    QString  m_propertyName;
    QVariant m_value;
};
}//namespace tcp
}//namespace core
}//namespace oplink
}//namespace elekdom
#endif // STATEVALUEMESSAGE_H
