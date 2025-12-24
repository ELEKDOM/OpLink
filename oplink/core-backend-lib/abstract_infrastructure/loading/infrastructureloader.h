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

#ifndef INFRASTRUCTURELOADER_H
#define INFRASTRUCTURELOADER_H

#include <QList>
#include <QSharedPointer>
#include "worker/worker.h"
#include "abstract_infrastructure/loading/infrastructurestore.h"
#include "abstract_infrastructure/loading/deviceprocessorbuilder.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "abstract_infrastructure/area/area.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT InfrastructureLoader : public plugframe::Worker, public InfrastructureStore
{
    Q_OBJECT

public:
    InfrastructureLoader(const QString& logChannel,
                         InfrastructureLoadingOperations& infrastructure);
    virtual ~InfrastructureLoader();

public:
    void buildDeviceBuilder();
    bool startLoadingInfrastructure(const QString& confFileName);

protected:
    virtual DeviceProcessorBuilder *createDeviceProcessorBuilder() = 0;
    virtual DeviceBuilder *createDeviceBuilder(const QspDeviceProcessorBuilder& processorBuilder) = 0;

protected: // Store
    virtual bool checkInfrastructureName(const QString& name);
    virtual bool addArea(const QString& areaName);
    virtual bool addGateway(GatewayArgs& gatewayArgs);
    virtual bool addLoad(const QString& loadName,
                         const QString& observableModelName,
                         const QString& localisation);
    virtual bool addActuator(const QString& actuatorName,
                             const QString& observableModelName,
                             const QString& deviceId,
                             const QString& deviceModelName,
                             const QString& localisation,
                             const ActuatorOutputsBinding& outputsBinding,
                             const DeviceChannelsBinding& deviceChannelsBinding);
    virtual bool addSensor(const QString& sensorName,
                           const QString& observableModelName,
                           const QString& deviceId,
                           const QString& deviceModelName,
                           const QString& localisation,
                           const DeviceChannelsBinding& deviceChannelsBinding);
    virtual plugframe::WorkerOuts *readFinished(bool readStatus);

protected:
    virtual Area *createArea(const QString& areaName) = 0;
    virtual AreaGateway *createGateway(GatewayArgs &gatewayArgs) = 0;

private: // Worker
    plugframe::WorkerArgs *createLoaderWorkerArgs(const QString &confFileName);
    plugframe::WorkerOuts *createLoaderWorkerOuts();

private:
    InfrastructureLoadingOperations& m_infrastructure;
    QspDeviceBuilder                 m_deviceBuilder;
    QspObservableBuildersContainer   m_loadedObservables;
    QList<QspArea>                   m_loadedAreas;
    QspArea                          m_curArea; // keeps the area in loading progress
    InfrastructureName               m_infrastructureName;
};
using QspInfrastructureLoader = QSharedPointer<InfrastructureLoader>;
}//namespace oplink
#endif // INFRASTRUCTURELOADER_H
