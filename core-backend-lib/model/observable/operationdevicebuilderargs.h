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

#ifndef OPERATIONDEVICEBUILDERARGS_H
#define OPERATIONDEVICEBUILDERARGS_H

#include <QSharedPointer>
#include "model/observable/observablebuilderargs.h"
#include "observable/observablenames.h"
#include "model/modelnames.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT OperationDeviceBuilderArgs : public ObservableBuilderArgs
{
public:
    OperationDeviceBuilderArgs(const ObservableName& observableName,
                               const ObservableModelName& observableModelName,
                               const LocalisationName& observableLocalisation,
                               const DeviceId& deviceId,
                               const DeviceModelName& deviceModelName,
                               const QspDeviceBuilder& deviceBuilder,
                               const DeviceChannelsBinding& deviceChannelsBinding);
    ~OperationDeviceBuilderArgs() override;

public:
    void setDevice(const QspDevice& device) {m_device = device;}

public:
    const DeviceId&              m_deviceId;
    const DeviceModelName&       m_deviceModelName;
    const QspDeviceBuilder&      m_deviceBuilder;
    QspDevice                    m_device;
    const DeviceChannelsBinding& m_deviceChannelsBinding;
};
using QspOperationDeviceBuilderArgs = QSharedPointer<OperationDeviceBuilderArgs>;
}//namespace oplink
#endif // OPERATIONDEVICEBUILDERARGS_H
