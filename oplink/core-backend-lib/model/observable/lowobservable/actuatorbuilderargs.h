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


#ifndef ACTUATORBUILDERARGS_H
#define ACTUATORBUILDERARGS_H
#include <QSharedPointer>
#include "observable/observablenames.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "model/modelnames.h"
#include "model/observable/lowobservable/operationdevicebuilderargs.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ActuatorBuilderArgs : public OperationDeviceBuilderArgs
{
public:
    ActuatorBuilderArgs(const ObservableName& observableName,
                        const ObservableModelName& observableModelName,
                        const LocalisationName& observableLocalisation,
                        const DeviceId& deviceId,
                        const DeviceModelName& deviceModelName,
                        const QspDeviceBuilder& deviceBuilder,
                        const DeviceChannelsBinding& deviceChannelsBinding,
                        const ActuatorOutputsBinding& actuatorOutputsBinding,
                        const QspObservableBuildersContainer& loadedObservables);
    ~ActuatorBuilderArgs() override;

public:
    const ActuatorOutputsBinding&         m_actuatorOutputsBinding;
    const QspObservableBuildersContainer& m_loadedObservables;
};
using QspActuatorBuilderArgs = QSharedPointer<ActuatorBuilderArgs>;
}//namespace oplink
#endif // ACTUATORBUILDERARGS_H
