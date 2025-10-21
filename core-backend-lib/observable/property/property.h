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

#ifndef PROPERTY_H
#define PROPERTY_H

#include <QSharedPointer>
#include <QVariant>
#include "logger/loggable.h"
#include "observable/observablenames.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT Property : public plugframe::Loggable
{
public:
    Property(Observable& observable,
             const PropertyName& propertyName,
             QMetaType::Type valueType);

    ~Property() override;

public:
    Observable& observable() {return m_observable;}
    const PropertyName& name(){return m_name;}
    const QVariant& value(){return m_value;}
    void value(const QVariant& val);
    bool isValidValue() {return m_validValue;}
    virtual void changeValue(const QVariant& val);

private:
    Observable&     m_observable;
    PropertyName    m_name;
    QVariant        m_value;
    QMetaType::Type m_valueType;
    bool            m_validValue;
};
using QspProperty = QSharedPointer<Property>;
}//namespace oplink
#endif // PROPERTY_H
