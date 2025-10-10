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


#ifndef SENSORPROPERTYMODEL_H
#define SENSORPROPERTYMODEL_H

#include "olcore-backend-lib_export.h"
#include "operationdevicepropertymodel.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT SensorPropertyModel : public OperationDevicePropertyModel
{
public:
    SensorPropertyModel(const PropertyModelName& modelName,
                           const observable::PropertyName& propertyName,
                           QVariant::Type valueType);
    ~SensorPropertyModel() override;

protected:
    observable::Property *createProperty(observable::Observable& observable) override;
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // SENSORPROPERTYMODEL_H
