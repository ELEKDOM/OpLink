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

#include "infrastructure.h"
#include "abstract_infrastructure/infrastructurefactory.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "abstract_infrastructure/loading/infrastructureloader.h"
#include "abstract_infrastructure/area/area.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "observable/observable/observablebuilder.h"
#include "worker/workerwatcher.h"
#include "bundle/bundlecontext.h"
#include "logger/pflog.h"
#include "model/observable/loadbuilderargs.h"
#include "model/observable/actuatorbuilderargs.h"
#include "model/observable/sensorbuilderargs.h"
#include "service-int/observablebuilderserviceinterface.h"

oplink::Infrastructure::Infrastructure(QString logBundleName, QString infrastructureName):
    plugframe::BundleImplementation{logBundleName},
    m_infrastructureName {infrastructureName},
    m_infraState {InfrastructureState::Created}
{
}

oplink::Infrastructure::~Infrastructure()
{

}

oplink::LoadBuilderArgs *oplink::Infrastructure::createLoadBuilderArgs(const oplink::ObservableName& loadName,
                                                                       const oplink::ObservableModelName& observableModelName,
                                                                       const oplink::LocalisationName& loadLocalisation)
{
    return new oplink::LoadBuilderArgs(loadName, observableModelName, loadLocalisation);
}

oplink::ActuatorBuilderArgs *oplink::Infrastructure::createActuatorBuilderArgs(const oplink::ObservableName& actuatorName,
                                                                               const oplink::ObservableModelName& observableModelName,
                                                                               const oplink::DeviceId& deviceId,
                                                                               const oplink::DeviceModelName& deviceModelName,
                                                                               const oplink::LocalisationName& actuatorLocalisation,
                                                                               const oplink::QspDeviceBuilder& deviceBuilder,
                                                                               const oplink::DeviceChannelsBinding& deviceChannelsBinding,
                                                                               const oplink::ActuatorOutputsBinding &outputsBinding,
                                                                               const oplink::QspObservableBuildersContainer& loadedObservables)
{
    return new oplink::ActuatorBuilderArgs(actuatorName,
                                           observableModelName,
                                           actuatorLocalisation,
                                           deviceId,
                                           deviceModelName,
                                           deviceBuilder,
                                           deviceChannelsBinding,
                                           outputsBinding,
                                           loadedObservables);
}

oplink::SensorBuilderArgs *oplink::Infrastructure::createSensorBuilderArgs(const oplink::ObservableName& sensorName,
                                                                           const oplink::ObservableModelName& observableModelName,
                                                                           const oplink::DeviceId& deviceId,
                                                                           const oplink::DeviceModelName& deviceModelName,
                                                                           const oplink::LocalisationName sensorLocalisation,
                                                                           const oplink::QspDeviceBuilder& deviceBuilder,
                                                                           const oplink::DeviceChannelsBinding& deviceChannelsBinding)
{
    return new oplink::SensorBuilderArgs(sensorName,
                                         observableModelName,
                                         sensorLocalisation,
                                         deviceId,
                                         deviceModelName,
                                         deviceBuilder,
                                         deviceChannelsBinding);
}

bool oplink::Infrastructure::startLoadingInfrastructure(oplink::InfrastructureControlServiceInterface::OperationalMode mode,
                                                        plugframe::WorkerWatcher *workerWatcher)
{
    QMutexLocker lock{&m_mutex};

    bool ret{false};

    if (m_infraState == InfrastructureState::Registered)
    {
        if (m_loader.isNull())
        {
            buildLoader(mode);
            if (!m_loader.isNull())
            {
                QString confFile {getConfPath()};  // config file name

                // Set Connection for work finished signal
                workerWatcher->connectWorker(m_loader.get());

                // Starts loading in background
                ret = m_loader->startLoadingInfrastructure(confFile);
            }
        }

        if (ret)
        {
            setLoading();
        }
        else
        {
            setError();
        }
    }
    return ret;
}

plugframe::BundleFactory *oplink::Infrastructure::createFactory()
{
    return new oplink::InfrastructureFactory;
}

plugframe::ServiceInterface *oplink::Infrastructure::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (oplink::InfrastructureControlServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<oplink::InfrastructureControlServiceInterface*>(getQplugin());
        setRegistered();
    }

    return ret;
}

const QString& oplink::Infrastructure::getInfrastructureName()
{
    return m_infrastructureName;
}

bool oplink::Infrastructure::loadingFinished()
{
    return m_infraState == InfrastructureState::Loaded || m_infraState == InfrastructureState::Error;
}

bool oplink::Infrastructure::checkInfrastructureName(const QString &name)
{
    return name == m_infrastructureName;
}

bool oplink::Infrastructure::isAreaAlreadyExist(const QString &areaName)
{
    return m_areas.contains(areaName);
}

void oplink::Infrastructure::addArea(const oplink::QspArea& newArea)
{
    m_areas.insert(newArea->name(), newArea);
    emit newArea->devicesLoaded(); // to synchronize initial devices state
}

oplink::QspObservableBuilder oplink::Infrastructure::buildLoadInstance(const oplink::ObservableName& loadName,
                                                                       const oplink::ObservableModelName& observableModelName,
                                                                       const oplink::LocalisationName& loadLocalisation)
{
    pfDebug3(logChannel()) << "->DeviceInfrastructure::buildLoadInstance, loadName=" << loadName << ", observableModelName=" << observableModelName << ", loadLocalisation=" << loadLocalisation;
    oplink::ObservableBuilderServiceInterface *obsBuilderService;
    obsBuilderService = bundleContext()->getService<oplink::ObservableBuilderServiceInterface>(oplink::ObservableBuilderServiceInterface::serviceName());

    oplink::QspLoadBuilderArgs builderArgs{createLoadBuilderArgs(loadName,
                                           observableModelName,
                                           loadLocalisation)};
    oplink::QspObservableBuilder ret{obsBuilderService->buildObservable(builderArgs)};
    pfDebug3(logChannel()) << "<-DeviceInfrastructure::buildLoadInstance, ret=" << ret;
    return ret;
 }

oplink::QspObservableBuilder oplink::Infrastructure::buildActuatorInstance(const oplink::ObservableName &actuatorName,
                                                                           const oplink::ObservableModelName &observableModelName,
                                                                           const oplink::DeviceId &deviceId,
                                                                           const oplink::DeviceModelName &deviceModelName,
                                                                           const oplink::LocalisationName &actuatorLocalisation,
                                                                           const oplink::QspDeviceBuilder &deviceBuilder,
                                                                           const oplink::DeviceChannelsBinding& deviceChannelsBinding,
                                                                           const oplink::ActuatorOutputsBinding &outputsBinding,
                                                                           const oplink::QspObservableBuildersContainer &loadedObservables)
{
    pfDebug3(logChannel()) << "->DeviceInfrastructure::buildActuatorInstance, actuatorName = " << actuatorName << ", observableModelName = " << observableModelName << ", deviceId = " << deviceId << ", deviceModelName = " << deviceModelName << ", actuatorLocalisation = " << actuatorLocalisation;
    oplink::ObservableBuilderServiceInterface *obsBuilderService;
    obsBuilderService = bundleContext()->getService<oplink::ObservableBuilderServiceInterface>(oplink::ObservableBuilderServiceInterface::serviceName());
    oplink::QspActuatorBuilderArgs builderArgs{createActuatorBuilderArgs(actuatorName,
                                                                         observableModelName,
                                                                         deviceId,
                                                                         deviceModelName,
                                                                         actuatorLocalisation,
                                                                         deviceBuilder,
                                                                         deviceChannelsBinding,
                                                                         outputsBinding,
                                                                         loadedObservables)};
    oplink::QspObservableBuilder ret{obsBuilderService->buildObservable(builderArgs)};
    pfDebug3(logChannel()) << "<-DeviceInfrastructure::buildActuatorInstance, ret=" << ret;
    return ret;
 }

oplink::QspObservableBuilder oplink::Infrastructure::buildSensorInstance(const oplink::ObservableName &sensorName,
                                                                         const oplink::ObservableModelName &observableModelName,
                                                                         const oplink::DeviceId &deviceId,
                                                                         const oplink::DeviceModelName &deviceModelName,
                                                                         const oplink::LocalisationName &sensorLocalisation,
                                                                         const oplink::QspDeviceBuilder &deviceBuilder,
                                                                         const oplink::DeviceChannelsBinding& deviceChannelsBinding)
{
    pfDebug3(logChannel()) << "->DeviceInfrastructure::buildSensorInstance, sensorName=" << sensorName << ", observableModelName=" << observableModelName << ", deviceId=" << deviceId << ", deviceModelName=" << deviceModelName << ", sensorLocalisation=" << sensorLocalisation;
    oplink::ObservableBuilderServiceInterface *obsBuilderService;
    obsBuilderService = bundleContext()->getService<oplink::ObservableBuilderServiceInterface>(oplink::ObservableBuilderServiceInterface::serviceName());
    oplink::QspSensorBuilderArgs builderArgs{createSensorBuilderArgs(sensorName,
                                                                     observableModelName,
                                                                     deviceId,
                                                                     deviceModelName,
                                                                     sensorLocalisation,
                                                                     deviceBuilder,
                                                                     deviceChannelsBinding)};
    oplink::QspObservableBuilder ret{obsBuilderService->buildObservable(builderArgs)};
    pfDebug3(logChannel()) << "<-DeviceInfrastructure::buildSensorInstance, ret=" << ret;
    return ret;
}

void oplink::Infrastructure::LoadingOk()
{
    setLoaded();
}

void oplink::Infrastructure::LoadingKo()
{
    setError();
}

bool oplink::Infrastructure::isLoaded()
{
    return m_infraState == InfrastructureState::Loaded;
}

void oplink::Infrastructure::buildLoader(oplink::InfrastructureControlServiceInterface::OperationalMode mode)
{
    if (mode == oplink::InfrastructureControlServiceInterface::OperationalMode::Operating)
    {
        m_loader.reset(createOperatingLoader(logChannel()));
    }
    else if (mode == oplink::InfrastructureControlServiceInterface::OperationalMode::Setup)
    {
        m_loader.reset(createSetupLoader(logChannel()));
    }

    m_loader->buildDeviceBuilder();
}
