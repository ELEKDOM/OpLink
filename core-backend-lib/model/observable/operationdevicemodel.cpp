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


#include "operationdevicemodel.h"
#include "model/observable/observablebuilderargs.h"
#include "model/observable/operationdevicebuilderargs.h"
#include "observable/observable/observablebuilder.h"
#include "observable/lowobservable/operationdevice.h"
#include "abstract_infrastructure/device/device.h"
#include "abstract_infrastructure/device/devicehook.h"
#include "abstract_infrastructure/loading/devicebuilder.h"

using namespace elekdom::oplink::core::model;
using namespace elekdom::oplink::core;

OperationDeviceModel::OperationDeviceModel(const ObservableModelName &name) :
    ObservableModel{name}
{

}

OperationDeviceModel::~OperationDeviceModel()
{

}

observable::ObservableBuilder *OperationDeviceModel::createInstance(QspObservableBuilderArgs builderArgs)
{
    observable::ObservableBuilder *ret{createObservable()};
    infrastructure::DeviceHook&    observableAsDeviceHook{dynamic_cast<infrastructure::DeviceHook&>(ret->toObservable())};
    QspOperationDeviceBuilderArgs  args{builderArgs.dynamicCast<OperationDeviceBuilderArgs>()};
    infrastructure::QspDevice      device{args->m_deviceBuilder->createDevice(args->m_deviceId,
                                                                                 args->m_deviceModelName,
                                                                                 observableAsDeviceHook)};
    args->setDevice(device); // needed during the command processor build phase!
    ret->setDevice(device);
    return ret;
}

void OperationDeviceModel::postBuild(observable::QspObservableBuilder observableBuilder, QspObservableBuilderArgs builderArgs)
{
    infrastructure::DeviceHook&    observableAsDeviceHook{dynamic_cast<infrastructure::DeviceHook&>(observableBuilder->toObservable())};
    QspOperationDeviceBuilderArgs  args{builderArgs.dynamicCast<OperationDeviceBuilderArgs>()};

    observableAsDeviceHook.bindChannels(args->m_deviceChannelsBinding);// device's channels binding
}

observable::ObservableBuilder *OperationDeviceModel::createObservable()
{
    return new observable::OperationDevice;
}
