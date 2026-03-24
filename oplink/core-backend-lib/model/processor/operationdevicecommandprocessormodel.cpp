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

#include "operationdevicecommandprocessormodel.h"
#include "model/observable/observablebuilderargs.h"
#include "model/observable/lowobservable/operationdevicebuilderargs.h"
#include "observable/processor/operationdevicecommandprocessor.h"
#include "abstract_infrastructure/device/devicecommandprocessor.h"
#include "abstract_infrastructure/loading/devicebuilder.h"

oplink::OperationDeviceCommandProcessorModel::OperationDeviceCommandProcessorModel(const oplink::ProcessorModelName& modelName,
                                                                                   const oplink::CommandName& commandName):
    LowCommandProcessorModel{modelName, commandName}
{

}

oplink::OperationDeviceCommandProcessorModel::~OperationDeviceCommandProcessorModel()
{

}

oplink::CommandProcessor *oplink::OperationDeviceCommandProcessorModel::createProcessor(const oplink::Observable &parent,
                                                                                        oplink::QspObservableBuilderArgs builderArgs)
{
    OperationDeviceCommandProcessor *ret;
    oplink::QspOperationDeviceBuilderArgs operationDeviceBuilderArgs{builderArgs.dynamicCast<oplink::OperationDeviceBuilderArgs>()};
    oplink::QspDeviceCommandProcessor deviceCommandProcessor{operationDeviceBuilderArgs->m_deviceBuilder->createDeviceProcessor(commandName(),
                                                                                                                                operationDeviceBuilderArgs->m_deviceModelName,
                                                                                                                                operationDeviceBuilderArgs->m_device)};
    ret = createInstance(parent, deviceCommandProcessor);
    return ret;
}
