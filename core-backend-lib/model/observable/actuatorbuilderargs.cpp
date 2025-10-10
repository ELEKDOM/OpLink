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

using namespace elekdom::oplink::core::model;

ActuatorBuilderArgs::ActuatorBuilderArgs(const observable::ObservableName& observableName,
                                               const ObservableModelName& observableModelName,
                                               const observable::LocalisationName& observableLocalisation,
                                               const infrastructure::DeviceId& deviceId,
                                               const infrastructure::DeviceModelName& deviceModelName,
                                               const infrastructure::QspDeviceBuilder& deviceBuilder,
                                               const infrastructure::DeviceChannelsBinding& deviceChannelsBinding,
                                               const infrastructure::ActuatorOutputsBinding& actuatorOutputsBinding,
                                               const observable::QspObservableBuildersContainer& loadedObservables):
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

ActuatorBuilderArgs::~ActuatorBuilderArgs()
{

}
