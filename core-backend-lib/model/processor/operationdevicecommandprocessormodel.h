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


#ifndef OPERATIONDEVICECOMMANDPROCESSORMODEL_H
#define OPERATIONDEVICECOMMANDPROCESSORMODEL_H

#include "olcore-backend-lib_export.h"
#include "lowcommandprocessormodel.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT OperationDeviceCommandProcessorModel : public LowCommandProcessorModel
{
public:
    OperationDeviceCommandProcessorModel(const ProcessorModelName& modelName,
                                            const command::CommandName& commandName);
    ~OperationDeviceCommandProcessorModel() override;

protected:
    observable::CommandProcessor *createProcessor(const observable::Observable& parent,
                                                     QspObservableBuilderArgs builderArgs)  override;
    virtual observable::OperationDeviceCommandProcessor *createInstance(const observable::Observable& parent,
                                                                           infrastructure::QspDeviceCommandProcessor deviceProcessor) = 0;
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OPERATIONDEVICECOMMANDPROCESSORMODEL_H
