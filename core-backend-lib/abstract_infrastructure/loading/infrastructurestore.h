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


#ifndef INFRASTRUCTURESTORE_H
#define INFRASTRUCTURESTORE_H

#include <QString>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "pfcore-lib_forward.h"
#include "logger/loggable.h"
#include "abstract_infrastructure/area/gatewayargs.h"

using namespace elekdom::plugframe::core;

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{

class OLCORE_BACKEND_LIB_EXPORT InfrastructureStore  : public logger::Loggable
{
public:
    InfrastructureStore(const QString& logChannel);
    ~InfrastructureStore() override;

public:
    virtual bool checkInfrastructureName(const QString& name) = 0;
    virtual bool addArea(const QString& areaName) = 0;
    virtual bool addGateway(GatewayArgs& gatewayArgs) = 0;
    virtual bool addLoad(const QString& loadName,
                         const QString& observableModelName,
                         const QString& localisation) = 0;
    virtual bool addActuator(const QString& actuatorName,
                             const QString& observableModelName,
                             const QString& deviceId,
                             const QString& deviceModelName,
                             const QString& localisation,
                             const ActuatorOutputsBinding& outputsBinding,
                             const DeviceChannelsBinding& deviceChannelsBinding) = 0;
    virtual bool addSensor(const QString& sensorName,
                           const QString& observableModelName,
                           const QString& deviceId,
                           const QString& deviceModelName,
                           const QString& localisation,
                           const DeviceChannelsBinding& deviceChannelsBinding) = 0;
    virtual worker::WorkerOuts *readFinished(bool readStatus) = 0;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace infrastructure

#endif // INFRASTRUCTURESTORE_H
