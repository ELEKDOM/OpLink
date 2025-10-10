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
#include "model/observable/operationdevicebuilderargs.h"
#include "abstract_infrastructure/device/devicecommandprocessor.h"
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "observable/processor/operationdevicecommandprocessor.h"

using namespace elekdom::oplink::core::model;
using namespace elekdom::oplink::core;

OperationDeviceCommandProcessorModel::OperationDeviceCommandProcessorModel(const ProcessorModelName& modelName,
                                                                                 const command::CommandName& commandName):
    LowCommandProcessorModel{modelName, commandName}
{

}

OperationDeviceCommandProcessorModel::~OperationDeviceCommandProcessorModel()
{

}

observable::CommandProcessor *OperationDeviceCommandProcessorModel::createProcessor(const observable::Observable &parent,
                                                                                          QspObservableBuilderArgs builderArgs)
{
    model::QspOperationDeviceBuilderArgs operationDeviceBuilderArgs{builderArgs.dynamicCast<OperationDeviceBuilderArgs>()};
    infrastructure::QspDeviceCommandProcessor deviceCommandProcessor{operationDeviceBuilderArgs->m_deviceBuilder->createDeviceProcessor(commandName(),
                                                                                                                                           operationDeviceBuilderArgs->m_deviceModelName,
                                                                                                                                           operationDeviceBuilderArgs->m_device)};

    return createInstance(parent, deviceCommandProcessor);
}
