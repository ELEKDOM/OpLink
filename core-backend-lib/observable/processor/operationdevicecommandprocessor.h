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


#ifndef OPERATIONDEVICECOMMANDPROCESSOR_H
#define OPERATIONDEVICECOMMANDPROCESSOR_H

#include "lowcommandprocessor.h"
#include "olcore-backend-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class OperationDeviceCommandProcessor : public LowCommandProcessor
{
public:
    OperationDeviceCommandProcessor(const Observable& observable,
                                       const command::CommandName& cmdName,
                                       const infrastructure::QspDeviceCommandProcessor& deviceProcessor);
    ~OperationDeviceCommandProcessor() override;

protected:
    void process(command::QspCommand order) override;
    virtual void setCheckStrategy(command::QspCommand cmd) = 0;

private:
    infrastructure::QspDeviceCommandProcessor m_deviceProcessor;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OPERATIONDEVICECOMMANDPROCESSOR_H
