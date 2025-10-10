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


#ifndef ACTUATORBUILDERARGS_H
#define ACTUATORBUILDERARGS_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "observable/observablenames.h"
#include "model/modelnames.h"
#include "model/observable/operationdevicebuilderargs.h"
#include "abstract_infrastructure/infrastructure-names.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT ActuatorBuilderArgs : public OperationDeviceBuilderArgs
{
public:
    ActuatorBuilderArgs(const observable::ObservableName& observableName,
                           const ObservableModelName& observableModelName,
                           const observable::LocalisationName& observableLocalisation,
                           const infrastructure::DeviceId& deviceId,
                           const infrastructure::DeviceModelName& deviceModelName,
                           const infrastructure::QspDeviceBuilder& deviceBuilder,
                           const infrastructure::DeviceChannelsBinding& deviceChannelsBinding,
                           const infrastructure::ActuatorOutputsBinding& actuatorOutputsBinding,
                           const observable::QspObservableBuildersContainer& loadedObservables);
    ~ActuatorBuilderArgs() override;

public:
    const infrastructure::ActuatorOutputsBinding& m_actuatorOutputsBinding;
    const observable::QspObservableBuildersContainer&    m_loadedObservables;
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace infrastructure

#endif // ACTUATORBUILDERARGS_H
