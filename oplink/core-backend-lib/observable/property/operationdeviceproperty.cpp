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

oplink::OperationDeviceProperty::OperationDeviceProperty(oplink::Observable& observable,
                                                         const oplink::PropertyName& propertyName):
    oplink::LowProperty{observable,
                        propertyName}
{

}

oplink::OperationDeviceProperty::~OperationDeviceProperty()
{

}

void oplink::OperationDeviceProperty::slave(oplink::QspLowProperty slaveProp)
{
    relatedProperty(slaveProp);
}

oplink::QspLowProperty oplink::OperationDeviceProperty::slave()
{
    return relatedProperty();
}

void oplink::OperationDeviceProperty::changeValue(const QVariant &val)
{
    oplink::LowProperty::changeValue(val);
    oplink::QspLowProperty lp{slave()};
    if (!lp.isNull())
    {
        lp->changeValue(val);
    }
}


