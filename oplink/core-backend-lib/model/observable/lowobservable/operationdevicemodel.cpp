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
#include "model/observable/lowobservable/operationdevicebuilderargs.h"
#include "observable/observable/observablebuilder.h"
#include "observable/observable/lowobservable/operationdevice.h"
#include "abstract_infrastructure/device/device.h"
#include "abstract_infrastructure/device/devicehook.h"
#include "abstract_infrastructure/loading/devicebuilder.h"

oplink::OperationDeviceModel::OperationDeviceModel(const ObservableModelName &name) :
    ObservableModel{name}
{

}

oplink::OperationDeviceModel::~OperationDeviceModel()
{

}

oplink::ObservableBuilder *oplink::OperationDeviceModel::createInstance(oplink::QspObservableBuilderArgs builderArgs)
{
    oplink::ObservableBuilder *ret{createObservable()};
    oplink::DeviceHook&    observableAsDeviceHook{dynamic_cast<oplink::DeviceHook&>(ret->toObservable())};
    oplink::QspOperationDeviceBuilderArgs  args{builderArgs.dynamicCast<oplink::OperationDeviceBuilderArgs>()};
    oplink::QspDevice      device{args->m_deviceBuilder->createDevice(args->m_deviceId,
                                                                      args->m_deviceModelName,
                                                                      observableAsDeviceHook)};
    args->setDevice(device); // needed during the command processor build phase!
    ret->setDevice(device);
    return ret;
}

void oplink::OperationDeviceModel::postBuild(oplink::QspObservableBuilder observableBuilder,
                                             oplink::QspObservableBuilderArgs builderArgs)
{
    oplink::DeviceHook&    observableAsDeviceHook{dynamic_cast<oplink::DeviceHook&>(observableBuilder->toObservable())};
    oplink::QspOperationDeviceBuilderArgs  args{builderArgs.dynamicCast<oplink::OperationDeviceBuilderArgs>()};

    observableAsDeviceHook.bindChannels(args->m_deviceChannelsBinding);// device's channels binding
}

oplink::ObservableBuilder *oplink::OperationDeviceModel::createObservable()
{
    return new oplink::OperationDevice;
}
