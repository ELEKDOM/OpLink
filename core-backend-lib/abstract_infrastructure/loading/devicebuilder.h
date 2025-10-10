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


#ifndef DEVICEBUILDER_H
#define DEVICEBUILDER_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "command/command-names.h"
#include "abstract_infrastructure/infrastructure-names.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{

class OLCORE_BACKEND_LIB_EXPORT DeviceBuilder
{
public:
    DeviceBuilder(const QspDeviceProcessorBuilder& processorBuilder);
    virtual ~DeviceBuilder();

public:
    QSharedPointer<DeviceCommandProcessor> createDeviceProcessor(const command::CommandName& commandName,
                                                                    const DeviceModelName& deviceModelName,
                                                                    const QspDevice& device);
    virtual QSharedPointer<Device> createDevice(const DeviceId& id,
                                                   const DeviceModelName& deviceModelName,
                                                   DeviceHook& deviceHook) = 0;
private:
    QspDeviceProcessorBuilder m_processorBuilder;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // DEVICEBUILDER_H
