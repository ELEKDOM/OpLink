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

#include <QVariant>
#include "device.h"
#include "devicehook.h"

oplink::Device::Device(const QString& logChannel,
                       const oplink::DeviceId& id,
                       oplink::DeviceHook& deviceHook):
                       plugframe::Loggable{logChannel},
                       m_id{id},
                       m_deviceHook{deviceHook}
{

}

oplink::Device::~Device()
{

}

void oplink::Device::setChannelValue(int idx, QVariant value)
{
    m_deviceHook.setChannelValue(idx, value);
}

bool oplink::Device::getChannelIdx(const oplink::PropertyName &propertyName, int &idx)
{
    return m_deviceHook.getChannelIdx(propertyName, idx);
}

bool oplink::Device::hasChannel(int idx)
{
    return m_deviceHook.hasChannel(idx);
}

