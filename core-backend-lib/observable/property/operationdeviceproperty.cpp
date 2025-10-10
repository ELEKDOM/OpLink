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


#include "operationdeviceproperty.h"
#include "observable/property/loadproperty.h"

using namespace elekdom::oplink::core::observable;

OperationDeviceProperty::OperationDeviceProperty(Observable& observable,
                                                       const PropertyName& propertyName,
                                                       QVariant::Type valueType):
    LowProperty{observable,
                   propertyName,
                   valueType}
{

}

OperationDeviceProperty::~OperationDeviceProperty()
{

}

void OperationDeviceProperty::slave(QspLoadProperty slaveProp)
{
    relatedProperty(slaveProp);
}

QSharedPointer<LoadProperty> OperationDeviceProperty::slave()
{
    QspLowProperty related{relatedProperty()};

    return related.dynamicCast<LoadProperty>();
}

void OperationDeviceProperty::changeValue(const QVariant &val)
{
    LowProperty::changeValue(val);
    QSharedPointer<LoadProperty> lp{slave()};
    if (!lp.isNull())
    {
        lp->changeValue(val);
    }
}


