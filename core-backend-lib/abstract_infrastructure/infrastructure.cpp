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

using namespace elekdom::plugframe::core;
using namespace elekdom::oplink::core::infrastructure::bundle;
using namespace elekdom::oplink::core;

Infrastructure::Infrastructure(QString logBundleName, QString infrastructureName):
    plugframe::core::bundle::BundleImplementation{logBundleName},
    m_infrastructureName {infrastructureName},
    m_infraState {InfrastructureState::Created}
{
}

Infrastructure::~Infrastructure()
{

}

model::LoadBuilderArgs *Infrastructure::createLoadBuilderArgs(const observable::ObservableName& loadName,
                                                                    const model::ObservableModelName& observableModelName,
                                                                    const observable::LocalisationName& loadLocalisation)
{
    return new model::LoadBuilderArgs(loadName, observableModelName, loadLocalisation);
}

model::ActuatorBuilderArgs *Infrastructure::createActuatorBuilderArgs(const observable::ObservableName& actuatorName,
                                                                            const model::ObservableModelName& observableModelName,
                                                                            const DeviceId& deviceId,
                                                                            const DeviceModelName& deviceModelName,
                                                                            const observable::LocalisationName& actuatorLocalisation,
                                                                            const QspDeviceBuilder& deviceBuilder,
                                                                            const DeviceChannelsBinding& deviceChannelsBinding,
                                                                            const ActuatorOutputsBinding &outputsBinding,
                                                                            const observable::QspObservableBuildersContainer& loadedObservables)
{
    return new core::model::ActuatorBuilderArgs(actuatorName,
                                                   observableModelName,
                                                   actuatorLocalisation,
                                                   deviceId,
                                                   deviceModelName,
                                                   deviceBuilder,
                                                   deviceChannelsBinding,
                                                   outputsBinding,
                                                   loadedObservables);
}

model::SensorBuilderArgs *Infrastructure::createSensorBuilderArgs(const observable::ObservableName& sensorName,
                                                                        const model::ObservableModelName& observableModelName,
                                                                        const DeviceId& deviceId,
                                                                        const DeviceModelName& deviceModelName,
                                                                        const observable::LocalisationName sensorLocalisation,
                                                                        const QspDeviceBuilder& deviceBuilder,
                                                                        const DeviceChannelsBinding& deviceChannelsBinding)
{
    return new core::model::SensorBuilderArgs(sensorName,
                                                 observableModelName,
                                                 sensorLocalisation,
                                                 deviceId,
                                                 deviceModelName,
                                                 deviceBuilder,
                                                 deviceChannelsBinding);
}

bool Infrastructure::startLoadingInfrastructure(service::InfrastructureControlServiceInterface::OperationalMode mode,
                                                   worker::WorkerWatcher *workerWatcher)
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

bundle::BundleFactory *Infrastructure::createFactory()
{
    return new factory::InfrastructureFactory;
}

plugin::ServiceInterface *Infrastructure::qtServiceInterface(const QString &sName)
{
    plugframe::core::plugin::ServiceInterface *ret{nullptr};

    if (service::InfrastructureControlServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<service::InfrastructureControlServiceInterface*>(getQplugin());
        setRegistered();
    }

    return ret;
}

const QString& Infrastructure::getInfrastructureName()
{
    return m_infrastructureName;
}

bool Infrastructure::loadingFinished()
{
    return m_infraState == InfrastructureState::Loaded || m_infraState == InfrastructureState::Error;
}

bool Infrastructure::checkInfrastructureName(const QString &name)
{
    return name == m_infrastructureName;
}

bool Infrastructure::isAreaAlreadyExist(const QString &areaName)
{
    return m_areas.contains(areaName);
}

void Infrastructure::addArea(const core::infrastructure::QspArea& newArea)
{
    m_areas.insert(newArea->name(), newArea);
    emit newArea->devicesLoaded(); // to synchronize initial devices state
}

observable::QspObservableBuilder Infrastructure::buildLoadInstance(const observable::ObservableName& loadName,
                                                                         const model::ObservableModelName& observableModelName,
                                                                         const observable::LocalisationName& loadLocalisation)
{
    pfDebug3(logChannel()) << "->DeviceInfrastructure::buildLoadInstance, loadName=" << loadName << ", observableModelName=" << observableModelName << ", loadLocalisation=" << loadLocalisation;
    observablemodelregister::service::ObservableBuilderServiceInterface *obsBuilderService;
    obsBuilderService = bundleContext()->getService<observablemodelregister::service::ObservableBuilderServiceInterface>(observablemodelregister::service::ObservableBuilderServiceInterface::serviceName());

    core::model::QspLoadBuilderArgs builderArgs{createLoadBuilderArgs(loadName,
                                                                         observableModelName,
                                                                        loadLocalisation)};
    core::observable::QspObservableBuilder ret{obsBuilderService->buildObservable(builderArgs)};
    pfDebug3(logChannel()) << "<-DeviceInfrastructure::buildLoadInstance, ret=" << ret;
    return ret;
 }

observable::QspObservableBuilder Infrastructure::buildActuatorInstance(const observable::ObservableName &actuatorName,
                                                                             const model::ObservableModelName &observableModelName,
                                                                             const infrastructure::DeviceId &deviceId,
                                                                             const infrastructure::DeviceModelName &deviceModelName,
                                                                             const core::observable::LocalisationName &actuatorLocalisation,
                                                                             const QspDeviceBuilder &deviceBuilder,
                                                                             const DeviceChannelsBinding& deviceChannelsBinding,
                                                                             const ActuatorOutputsBinding &outputsBinding,
                                                                             const core::observable::QspObservableBuildersContainer &loadedObservables)
{
    pfDebug3(logChannel()) << "->DeviceInfrastructure::buildActuatorInstance, actuatorName = " << actuatorName << ", observableModelName = " << observableModelName << ", deviceId = " << deviceId << ", deviceModelName = " << deviceModelName << ", actuatorLocalisation = " << actuatorLocalisation;
    observablemodelregister::service::ObservableBuilderServiceInterface *obsBuilderService;
    obsBuilderService = bundleContext()->getService<observablemodelregister::service::ObservableBuilderServiceInterface>(observablemodelregister::service::ObservableBuilderServiceInterface::serviceName());
    core::model::QspActuatorBuilderArgs builderArgs{createActuatorBuilderArgs(actuatorName,
                                                                                 observableModelName,
                                                                                 deviceId,
                                                                                 deviceModelName,
                                                                                 actuatorLocalisation,
                                                                                 deviceBuilder,
                                                                                 deviceChannelsBinding,
                                                                                 outputsBinding,
                                                                                 loadedObservables)};
    core::observable::QspObservableBuilder ret{obsBuilderService->buildObservable(builderArgs)};
    pfDebug3(logChannel()) << "<-DeviceInfrastructure::buildActuatorInstance, ret=" << ret;
    return ret;
 }

observable::QspObservableBuilder Infrastructure::buildSensorInstance(const observable::ObservableName &sensorName,
                                                                           const model::ObservableModelName &observableModelName,
                                                                           const infrastructure::DeviceId &deviceId,
                                                                           const infrastructure::DeviceModelName &deviceModelName,
                                                                           const observable::LocalisationName &sensorLocalisation,
                                                                           const QspDeviceBuilder &deviceBuilder,
                                                                           const DeviceChannelsBinding& deviceChannelsBinding)
{
    pfDebug3(logChannel()) << "->DeviceInfrastructure::buildSensorInstance, sensorName=" << sensorName << ", observableModelName=" << observableModelName << ", deviceId=" << deviceId << ", deviceModelName=" << deviceModelName << ", sensorLocalisation=" << sensorLocalisation;
    observablemodelregister::service::ObservableBuilderServiceInterface *obsBuilderService;
    obsBuilderService = bundleContext()->getService<observablemodelregister::service::ObservableBuilderServiceInterface>(observablemodelregister::service::ObservableBuilderServiceInterface::serviceName());
    core::model::QspSensorBuilderArgs builderArgs{createSensorBuilderArgs(sensorName,
                                                                             observableModelName,
                                                                             deviceId,
                                                                             deviceModelName,
                                                                             sensorLocalisation,
                                                                             deviceBuilder,
                                                                             deviceChannelsBinding)};
    core::observable::QspObservableBuilder ret{obsBuilderService->buildObservable(builderArgs)};
    pfDebug3(logChannel()) << "<-DeviceInfrastructure::buildSensorInstance, ret=" << ret;
    return ret;
}

void Infrastructure::LoadingOk()
{
    setLoaded();
}

void Infrastructure::LoadingKo()
{
    setError();
}

bool Infrastructure::isLoaded()
{
    return m_infraState == InfrastructureState::Loaded;
}

void Infrastructure::buildLoader(service::InfrastructureControlServiceInterface::OperationalMode mode)
{
    if (mode == service::InfrastructureControlServiceInterface::OperationalMode::Operating)
    {
        m_loader.reset(createOperatingLoader(logChannel()));
    }
    else if (mode == service::InfrastructureControlServiceInterface::OperationalMode::Setup)
    {
        m_loader.reset(createSetupLoader(logChannel()));
    }

    m_loader->buildDeviceBuilder();
}
