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

#ifndef DEVICEPROCESSORBUILDER_H
#define DEVICEPROCESSORBUILDER_H

#include <QSharedPointer>
#include "command/command-names.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "abstract_infrastructure/device/device.h"
#include "abstract_infrastructure/device/devicecommandprocessor.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT DeviceProcessorBuilder
{
public:
    DeviceProcessorBuilder();
    virtual ~DeviceProcessorBuilder();

public:
    virtual DeviceCommandProcessor *createDeviceProcessor(const CommandName& commandName,
                                                          const DeviceModelName& deviceModelName,
                                                          const QspDevice& device) = 0;
};
using QspDeviceProcessorBuilder = QSharedPointer<DeviceProcessorBuilder>;
}//namespace oplink
#endif // DEVICEPROCESSORBUILDER_H
