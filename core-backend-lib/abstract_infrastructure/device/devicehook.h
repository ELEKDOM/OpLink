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

#ifndef DEVICEHOOK_H
#define DEVICEHOOK_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "observable/observablenames.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT DeviceHook
{
public:
    virtual ~DeviceHook() {}

public:
    virtual void bindChannels(const DeviceChannelsBinding& deviceChannelsBinding) = 0;
    virtual void setChannelValue(int idx, QVariant value) = 0;
    virtual bool getChannelIdx(const oplink::PropertyName& propertyName, int& idx) = 0;
    virtual bool hasChannel(int idx) = 0;
};
}//namespace oplink
#endif // DEVICEHOOK_H
