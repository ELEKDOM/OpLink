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

#include "property.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class OLCORE_BACKEND_LIB_EXPORT LowProperty : public Property
{
private:
    QspLowProperty m_relatedProperty;

public:
    LowProperty(Observable& observable,
                   const PropertyName& propertyName,
                   QMetaType::Type valueType);
    ~LowProperty() override;

protected:
    QspLowProperty relatedProperty() {return m_relatedProperty;}
    void relatedProperty(QspLowProperty relatedProp) {m_relatedProperty = relatedProp;}
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // LOWPROPERTY_H
