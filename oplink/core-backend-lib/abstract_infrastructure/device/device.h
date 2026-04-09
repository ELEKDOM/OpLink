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

#ifndef DEVICE_H
#define DEVICE_H

#include <QSharedPointer>
#include "logger/loggable.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "observable/propertyid.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT Device : public plugframe::Loggable
{
private:
    DeviceId    m_id;
    DeviceHook& m_deviceHook;

public:
    Device(const QString& logChannel,
           const DeviceId& id,
           DeviceHook& deviceHook);

    ~Device() override;

public:
    const DeviceId& id() {return m_id;}
    void setChannelValue(int idx, QVariant value);
    bool getChannelIdx(const oplink::PropertyName& propertyName, int& idx);
    bool hasChannel(int idx);

public:
    virtual void recoverState() = 0;
};
using QspDevice = QSharedPointer<Device>;
}//namespace oplink
#endif // DEVICE_H
