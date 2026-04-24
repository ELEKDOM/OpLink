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

#ifndef EXPECTEDVALUECHECKCOMMANDPROCESSORMODEL_H
#define EXPECTEDVALUECHECKCOMMANDPROCESSORMODEL_H

#include "model/processor/lowprocessor/operationdevicecommandprocessormodel.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ExpectedValueCheckCommandProcessorModel : public OperationDeviceCommandProcessorModel
{
public:
    ExpectedValueCheckCommandProcessorModel(const ProcessorModelName& modelName,
                                            const CommandName& commandName);
    ~ExpectedValueCheckCommandProcessorModel() override;

protected:
    OperationDeviceCommandProcessor *createInstance(Observable& parent,
                                                    QspDeviceCommandProcessor deviceProcessor) override;

};
}//namespace oplink
#endif // EXPECTEDVALUECHECKCOMMANDPROCESSORMODEL_H
