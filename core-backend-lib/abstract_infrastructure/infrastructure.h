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

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "bundle/bundleimplementation.h"
#include "abstract_infrastructure/loading/infrastructureloadingoperations.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "service-int/infrastructurecontrolserviceinterface.h"
#include "observable/observablenames.h"
#include "model/modelnames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{
namespace bundle
{

class OLCORE_BACKEND_LIB_EXPORT Infrastructure : public plugframe::core::bundle::BundleImplementation,
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
    bool startLoadingInfrastructure(service::InfrastructureControlServiceInterface::OperationalMode mode,
                                    plugframe::core::worker::WorkerWatcher *workerWatcher);
protected:
    plugframe::core::bundle::BundleFactory* createFactory() override;
    plugframe::core::plugin::ServiceInterface *qtServiceInterface(const QString& sName) override;

protected:
    virtual InfrastructureLoader *createOperatingLoader(const QString& logChannel) = 0;
    virtual InfrastructureLoader *createSetupLoader(const QString& logChannel) = 0;
    virtual model::LoadBuilderArgs *createLoadBuilderArgs(const observable::ObservableName& loadName,
                                                             const model::ObservableModelName& observableModelName,
                                                             const observable::LocalisationName& loadLocalisation);
    virtual model::ActuatorBuilderArgs *createActuatorBuilderArgs(const observable::ObservableName& actuatorName,
                                                                     const model::ObservableModelName& observableModelName,
                                                                     const DeviceId& deviceId,
                                                                     const DeviceModelName& deviceModelName,
                                                                     const observable::LocalisationName& actuatorLocalisation,
                                                                     const QspDeviceBuilder& deviceBuilder,
                                                                     const DeviceChannelsBinding& deviceChannelsBinding,
                                                                     const ActuatorOutputsBinding &outputsBinding,
                                                                     const observable::QspObservableBuildersContainer& loadedObservables);
    virtual model::SensorBuilderArgs *createSensorBuilderArgs(const observable::ObservableName& sensorName,
                                                                 const model::ObservableModelName& observableModelName,
                                                                 const DeviceId& deviceId,
                                                                 const DeviceModelName& deviceModelName,
                                                                 const observable::LocalisationName sensorLocalisation,
                                                                 const QspDeviceBuilder& deviceBuilder,
                                                                 const DeviceChannelsBinding& deviceChannelsBinding);

protected: // EdDeviceInfrastructureLoadingOperations
    bool checkInfrastructureName(const QString& name) override;
    bool isAreaAlreadyExist(const QString& areaName) override;
    void addArea(const QspArea& newArea) override;
    observable::QspObservableBuilder buildLoadInstance(const observable::ObservableName& loadName,
                                                          const model::ObservableModelName& observableModelName,
                                                          const observable::LocalisationName& loadLocalisation) override;
    observable::QspObservableBuilder buildActuatorInstance(const observable::ObservableName& actuatorName,
                                                              const model::ObservableModelName& observableModelName,
                                                              const DeviceId& deviceId,
                                                              const DeviceModelName& deviceModelName,
                                                              const observable::LocalisationName& actuatorLocalisation,
                                                              const QspDeviceBuilder& deviceBuilder,
                                                              const DeviceChannelsBinding& deviceChannelsBinding,
                                                              const ActuatorOutputsBinding &outputsBinding,
                                                              const observable::QspObservableBuildersContainer& loadedObservables) override;
    observable::QspObservableBuilder buildSensorInstance(const observable::ObservableName& sensorName,
                                                            const model::ObservableModelName& observableModelName,
                                                            const DeviceId& deviceId,
                                                            const DeviceModelName& deviceModelName,
                                                            const observable::LocalisationName& sensorLocalisation,
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
    void buildLoader(service::InfrastructureControlServiceInterface::OperationalMode mode);

private:
    InfrastructureName      m_infrastructureName;
    InfrastructureState        m_infraState;
    QspInfrastructureLoader m_loader;
    QHash<QString, QspArea> m_areas;
};

}//namespace bundle
}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // INFRASTRUCTURE_H
