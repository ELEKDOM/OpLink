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


#include <QFile>
#include "infrastructureloader.h"
#include "abstract_infrastructure/loading/deviceprocessorbuilder.h"
#include "abstract_infrastructure/loading/infrastructureloadingoperations.h"
#include "abstract_infrastructure/loading/infrastructureloaderargs.h"
#include "abstract_infrastructure/loading/infrastructureloaderouts.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "abstract_infrastructure/area/area.h"
#include "observable/observable/observablebuilder.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "worker/workerargs.h"
#include "logger/pflog.h"

using namespace elekdom::oplink::core::infrastructure;

InfrastructureLoader::InfrastructureLoader(const QString& logChannel,
                                                 InfrastructureLoadingOperations& infrastructure):
    InfrastructureStore{logChannel},
    m_infrastructure{infrastructure}
{

}

InfrastructureLoader::~InfrastructureLoader()
{

}

void InfrastructureLoader::buildDeviceBuilder()
{
    QspDeviceProcessorBuilder processorBuilder{createDeviceProcessorBuilder()};
    m_deviceBuilder.reset(createDeviceBuilder(processorBuilder));
}

bool InfrastructureLoader::startLoadingInfrastructure(const QString &confFileName)
{
    bool ret{false};
    QFile cf{confFileName};

    ret = cf.exists();
    if (ret)
    {
        worker::QspWorkerArgs args{createLoaderWorkerArgs(confFileName)};

        m_loadedObservables.reset(new observable::ObservableBuildersContainer);

        // start worker in a background thread
        startWork(args);
    }
    else
    {
        pfWarning1(logChannel()) << tr("Impossible de trouver le fichier %1").arg(confFileName);
    }

    return ret;
}

bool InfrastructureLoader::checkInfrastructureName(const QString &name)
{
    m_infrastructureName = name;
    return m_infrastructure.checkInfrastructureName(m_infrastructureName);
}

bool InfrastructureLoader::addArea(const QString &areaName)
{
    bool found{false};
    QListIterator<QspArea> i(m_loadedAreas);

    while (i.hasNext() && !found)
    {
        found = (i.next())->name() == areaName;
    }

    if (!found)
    {
        m_curArea.reset(createArea(areaName));
        m_loadedAreas.append(m_curArea);
    }

    return !found;
}

bool InfrastructureLoader::addGateway(GatewayArgs& gatewayArgs)
{
    bool ret{m_curArea && m_curArea->haveNoGateway()};

    if (ret)
    {
        m_curArea->setGateway(createGateway(gatewayArgs));
    }

    return ret;
}

bool InfrastructureLoader::addLoad(const QString &loadName,
                                           const QString &observableModelName,
                                           const QString &localisation)
{
    bool            ret;

    ret = !m_loadedObservables->contains(loadName);
    if (ret)
    {
        observable::QspObservableBuilder load{m_infrastructure.buildLoadInstance(loadName,
                                                                                    observableModelName,
                                                                                    localisation)};
        ret = !load.isNull();
        if (ret)
        {
            m_loadedObservables->insert(loadName, load);
        }
    }

    return ret;
}

bool InfrastructureLoader::addActuator(const QString &actuatorName,
                                                const QString &observableModelName,
                                                const QString &deviceId,
                                                const QString &deviceModelName,
                                                const QString &localisation,
                                                const ActuatorOutputsBinding &outputsBinding,
                                                const DeviceChannelsBinding& deviceChannelsBinding)
{
    bool            ret;

    ret = !m_loadedObservables->contains(actuatorName);
    if (ret)
    {
        observable::QspObservableBuilder actuator{m_infrastructure.buildActuatorInstance(actuatorName,
                                                                                            observableModelName,
                                                                                            deviceId,
                                                                                            deviceModelName,
                                                                                            localisation,
                                                                                            m_deviceBuilder,
                                                                                            deviceChannelsBinding,
                                                                                            outputsBinding,
                                                                                            m_loadedObservables)};

        ret = !actuator.isNull();
        if (ret)
        {
            m_loadedObservables->insert(actuatorName, actuator); // a new actuator loaded
            m_curArea->addDevice(actuator->device());            // actuator is a device beloging to a area
        }
    }

    return ret;
}

bool InfrastructureLoader::addSensor(const QString &sensorName,
                                              const QString &observableModelName,
                                              const QString &deviceId,
                                              const QString &deviceModelName,
                                              const QString &localisation,
                                              const DeviceChannelsBinding& deviceChannelsBinding)
{
    bool            ret;

    ret = !m_loadedObservables->contains(sensorName);
    if (ret)
    {
        observable::QspObservableBuilder sensor{m_infrastructure.buildSensorInstance(sensorName,
                                                                                        observableModelName,
                                                                                        deviceId,
                                                                                        deviceModelName,
                                                                                        localisation,
                                                                                        m_deviceBuilder,
                                                                                        deviceChannelsBinding)};

        ret = !sensor.isNull();
        if (ret)
        {
            m_loadedObservables->insert(sensorName, sensor); // a new sensor loaded
            m_curArea->addDevice(sensor->device());          // sensor is a device beloging to a area
        }
    }

    return ret;
}

worker::WorkerOuts *InfrastructureLoader::readFinished(bool readStatus)
{
    if (readStatus)
    {
        // Add Areas into Infrastructure
        QListIterator<QspArea> i(m_loadedAreas);

        m_curArea.reset();
        while (i.hasNext())
        {
            m_infrastructure.addArea(i.next());
        }
        m_infrastructure.LoadingOk();
        m_loadedAreas.clear();
    }
    else
    {
        m_infrastructure.LoadingKo();
    }

    return createLoaderWorkerOuts();
}

worker::WorkerArgs *InfrastructureLoader::createLoaderWorkerArgs(const QString &confFileName)
{
    return new InfrastructureLoaderArgs{confFileName};
}

worker::WorkerOuts *InfrastructureLoader::createLoaderWorkerOuts()
{
    return new  InfrastructureLoaderOuts(m_infrastructureName,
                                            m_infrastructure.isLoaded(),
                                            m_loadedObservables);
}
