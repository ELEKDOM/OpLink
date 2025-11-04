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

#ifndef INFRASTRUCTURE_H
#define INFRASTRUCTURE_H

#include "bundle/bundleimplementation.h"
#include "abstract_infrastructure/loading/infrastructureloadingoperations.h"
#include "abstract_infrastructure/loading/infrastructureloader.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "service-int/infrastructurecontrolserviceinterface.h"
#include "observable/observablenames.h"
#include "model/modelnames.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT Infrastructure : public plugframe::BundleImplementation,
                                                 public InfrastructureLoadingOperations
{
public:
    enum class InfrastructureState {Created, Registered, Loading, Loaded, Error};

public:
    Infrastructure(QString logBundleName, QString infrastructureName);
    ~Infrastructure() override;

public: // for DeviceInfrastructureControlService
    virtual const QString& getInfrastructureName();
    bool loadingFinished();
    // infrastructure loading is realized by a worker task. At the end of loading, the workerwatcher is notified
    bool startLoadingInfrastructure(InfrastructureControlServiceInterface::OperationalMode mode,
                                    plugframe::WorkerWatcher *workerWatcher);
protected:
    plugframe::BundleFactory* createFactory() override;
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;

protected:
    virtual InfrastructureLoader *createOperatingLoader(const QString& logChannel) = 0;
    virtual InfrastructureLoader *createSetupLoader(const QString& logChannel) = 0;
    virtual LoadBuilderArgs *createLoadBuilderArgs(const ObservableName& loadName,
                                                   const ObservableModelName& observableModelName,
                                                   const LocalisationName& loadLocalisation);
    virtual ActuatorBuilderArgs *createActuatorBuilderArgs(const ObservableName& actuatorName,
                                                           const ObservableModelName& observableModelName,
                                                           const DeviceId& deviceId,
                                                           const DeviceModelName& deviceModelName,
                                                           const LocalisationName& actuatorLocalisation,
                                                           const QspDeviceBuilder& deviceBuilder,
                                                           const DeviceChannelsBinding& deviceChannelsBinding,
                                                           const ActuatorOutputsBinding &outputsBinding,
                                                           const QspObservableBuildersContainer& loadedObservables);
    virtual SensorBuilderArgs *createSensorBuilderArgs(const ObservableName& sensorName,
                                                       const ObservableModelName& observableModelName,
                                                       const DeviceId& deviceId,
                                                       const DeviceModelName& deviceModelName,
                                                       const LocalisationName sensorLocalisation,
                                                       const QspDeviceBuilder& deviceBuilder,
                                                       const DeviceChannelsBinding& deviceChannelsBinding);

protected: // EdDeviceInfrastructureLoadingOperations
    bool checkInfrastructureName(const QString& name) override;
    bool isAreaAlreadyExist(const QString& areaName) override;
    void addArea(const QspArea& newArea) override;
    QspObservableBuilder buildLoadInstance(const ObservableName& loadName,
                                           const ObservableModelName& observableModelName,
                                           const LocalisationName& loadLocalisation) override;
    QspObservableBuilder buildActuatorInstance(const ObservableName& actuatorName,
                                               const ObservableModelName& observableModelName,
                                               const DeviceId& deviceId,
                                               const DeviceModelName& deviceModelName,
                                               const LocalisationName& actuatorLocalisation,
                                               const QspDeviceBuilder& deviceBuilder,
                                               const DeviceChannelsBinding& deviceChannelsBinding,
                                               const ActuatorOutputsBinding &outputsBinding,
                                               const QspObservableBuildersContainer& loadedObservables) override;
    QspObservableBuilder buildSensorInstance(const ObservableName& sensorName,
                                             const ObservableModelName& observableModelName,
                                             const DeviceId& deviceId,
                                             const DeviceModelName& deviceModelName,
                                             const LocalisationName& sensorLocalisation,
                                             const QspDeviceBuilder& deviceBuilder,
                                             const DeviceChannelsBinding& deviceChannelsBinding) override;
    void LoadingOk() override;
    void LoadingKo() override;
    bool isLoaded() override;

private:
    void setRegistered() {m_infraState = InfrastructureState::Registered;}
    void setLoading() {m_infraState = InfrastructureState::Loading;}
    void setLoaded() {m_infraState = InfrastructureState::Loaded;}
    void setError() {m_infraState = InfrastructureState::Error;}
    void buildLoader(InfrastructureControlServiceInterface::OperationalMode mode);

private:
    InfrastructureName      m_infrastructureName;
    InfrastructureState     m_infraState;
    QspInfrastructureLoader m_loader;
    QHash<QString, QspArea> m_areas;
};
}//namespace oplink
#endif // INFRASTRUCTURE_H
