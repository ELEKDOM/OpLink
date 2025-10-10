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


#ifndef SENSORBUILDERARGS_H
#define SENSORBUILDERARGS_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "model/observable/operationdevicebuilderargs.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT SensorBuilderArgs : public OperationDeviceBuilderArgs
{
public:
    SensorBuilderArgs(const observable::ObservableName& observableName,
                         const ObservableModelName& observableModelName,
                         const observable::LocalisationName& observableLocalisation,
                         const infrastructure::DeviceId& deviceId,
                         const infrastructure::DeviceModelName& deviceModelName,
                         const infrastructure::QspDeviceBuilder& deviceBuilder,
                         const infrastructure::DeviceChannelsBinding& deviceChannelsBinding);
    ~SensorBuilderArgs() override;
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // SENSORBUILDERARGS_H
