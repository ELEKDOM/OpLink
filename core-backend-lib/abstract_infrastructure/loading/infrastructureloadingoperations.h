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
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "observable/observablenames.h"
#include "model/modelnames.h"
#include "abstract_infrastructure/infrastructure-names.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{

class OLCORE_BACKEND_LIB_EXPORT InfrastructureLoadingOperations
{
public:
    virtual ~InfrastructureLoadingOperations() {}

public:
    virtual bool checkInfrastructureName(const QString& name) = 0;
    virtual bool isAreaAlreadyExist(const QString& areaName) = 0;
    virtual void addArea(const QspArea& newArea) = 0;
    virtual observable::QspObservableBuilder buildLoadInstance(const observable::ObservableName& loadName,
                                                                  const model::ObservableModelName& observableModelName,
                                                                  const observable::LocalisationName& loadLocalisation) = 0;
    virtual observable::QspObservableBuilder buildActuatorInstance(const observable::ObservableName& actuatorName,
                                                                      const model::ObservableModelName& observableModelName,
                                                                      const DeviceId& deviceId,
                                                                      const DeviceModelName& deviceModelName,
                                                                      const observable::LocalisationName& actuatorLocalisation,
                                                                      const QspDeviceBuilder& deviceCommunicationBuilder,
                                                                      const DeviceChannelsBinding& deviceChannelsBinding,
                                                                      const ActuatorOutputsBinding &outputsBinding,
                                                                      const observable::QspObservableBuildersContainer& loadedObservables) = 0;
    virtual observable::QspObservableBuilder buildSensorInstance(const observable::ObservableName& sensorName,
                                                                    const model::ObservableModelName& observableModelName,
                                                                    const DeviceId& deviceId,
                                                                    const DeviceModelName& deviceModelName,
                                                                    const observable::LocalisationName& sensorLocalisation,
                                                                    const QspDeviceBuilder& deviceCommunicationBuilder,
                                                                    const DeviceChannelsBinding& deviceChannelsBinding) = 0;
    virtual void LoadingOk() = 0;
    virtual void LoadingKo() = 0;
    virtual bool isLoaded() = 0;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // INFRASTRUCTURELOADINGOPERATIONS_H
