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

#ifndef INFRASTRUCTURELOADINGOPERATIONS_H
#define INFRASTRUCTURELOADINGOPERATIONS_H

#include <QString>
#include "observable/observablenames.h"
#include "model/modelnames.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "abstract_infrastructure/area/area.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "observable/observable/observablebuilder.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT InfrastructureLoadingOperations
{
public:
    virtual ~InfrastructureLoadingOperations() {}

public:
    virtual bool checkInfrastructureName(const QString& name) = 0;
    virtual bool isAreaAlreadyExist(const QString& areaName) = 0;
    virtual void addArea(const QspArea& newArea) = 0;
    virtual QspObservableBuilder buildLoadInstance(const ObservableName& loadName,
                                                   const ObservableModelName& observableModelName,
                                                   const LocalisationName& loadLocalisation) = 0;
    virtual QspObservableBuilder buildActuatorInstance(const ObservableName& actuatorName,
                                                       const ObservableModelName& observableModelName,
                                                       const DeviceId& deviceId,
                                                       const DeviceModelName& deviceModelName,
                                                       const LocalisationName& actuatorLocalisation,
                                                       const QspDeviceBuilder& deviceCommunicationBuilder,
                                                       const DeviceChannelsBinding& deviceChannelsBinding,
                                                       const ActuatorOutputsBinding &outputsBinding,
                                                       const QspObservableBuildersContainer& loadedObservables) = 0;
    virtual QspObservableBuilder buildSensorInstance(const ObservableName& sensorName,
                                                     const ObservableModelName& observableModelName,
                                                     const DeviceId& deviceId,
                                                     const DeviceModelName& deviceModelName,
                                                     const LocalisationName& sensorLocalisation,
                                                     const QspDeviceBuilder& deviceCommunicationBuilder,
                                                     const DeviceChannelsBinding& deviceChannelsBinding) = 0;
    virtual void LoadingOk() = 0;
    virtual void LoadingKo() = 0;
    virtual bool isLoaded() = 0;
};
}//namespace oplink
#endif // INFRASTRUCTURELOADINGOPERATIONS_H
