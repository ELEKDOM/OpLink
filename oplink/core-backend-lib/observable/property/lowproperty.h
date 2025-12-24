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

#ifndef LOWPROPERTY_H
#define LOWPROPERTY_H

#include <QSharedPointer>
#include "property.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT LowProperty : public Property
{
public:
    LowProperty(Observable& observable,
                const PropertyName& propertyName,
                QMetaType::Type valueType);
    ~LowProperty() override;

protected:
    QSharedPointer<LowProperty> relatedProperty() {return m_relatedProperty;}
    void relatedProperty(QSharedPointer<LowProperty> relatedProp) {m_relatedProperty = relatedProp;}

private:
    QSharedPointer<LowProperty> m_relatedProperty;
};
using QspLowProperty = QSharedPointer<LowProperty>;
}//namespace oplink
#endif // LOWPROPERTY_H
