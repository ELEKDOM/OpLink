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

#include "actuatorbuilderargs.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "observable/observable/observablebuilderscontainer.h"

oplink::ActuatorBuilderArgs::ActuatorBuilderArgs(const oplink::ObservableName& observableName,
                                                 const oplink::ObservableModelName& observableModelName,
                                                 const oplink::LocalisationName& observableLocalisation,
                                                 const oplink::DeviceId& deviceId,
                                                 const oplink::DeviceModelName& deviceModelName,
                                                 const oplink::QspDeviceBuilder& deviceBuilder,
                                                 const oplink::DeviceChannelsBinding& deviceChannelsBinding,
                                                 const oplink::ActuatorOutputsBinding& actuatorOutputsBinding,
                                                 const oplink::QspObservableBuildersContainer& loadedObservables):
    OperationDeviceBuilderArgs{observableName,
                               observableModelName,
                               observableLocalisation,
                               deviceId,
                               deviceModelName,
                               deviceBuilder,
                               deviceChannelsBinding},
    m_actuatorOutputsBinding{actuatorOutputsBinding},
    m_loadedObservables{loadedObservables}
{

}

oplink::ActuatorBuilderArgs::~ActuatorBuilderArgs()
{

}
