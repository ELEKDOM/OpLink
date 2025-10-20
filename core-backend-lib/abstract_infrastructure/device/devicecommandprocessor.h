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

#ifndef DEVICECOMMANDPROCESSOR_H
#define DEVICECOMMANDPROCESSOR_H

#include <QSharedPointer>
#include "logger/loggable.h"
#include "observable/observablenames.h"
#include "command/command.h"
#include "device.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT DeviceCommandProcessor : public plugframe::Loggable
{
public:
    DeviceCommandProcessor(const QString& logChannel,
                           const QspDevice& device);
    virtual ~DeviceCommandProcessor();

public:
    virtual void processDeviceCmd(QspCommand order) = 0;

protected:
    const QspDevice& device() {return m_device;}
    bool getChannelIdx(const PropertyName& propertyName, int& idx);

private:
    QspDevice m_device;
};
using QspDeviceCommandProcessor = QSharedPointer<DeviceCommandProcessor>;
}//namespace oplink
#endif // DEVICECOMMANDPROCESSOR_H
