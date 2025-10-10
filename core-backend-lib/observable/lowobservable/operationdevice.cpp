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


#include "operationdevice.h"
#include "logger/pflog.h"
#include "observable/property/operationdeviceproperty.h"
#include "abstract_infrastructure/loading/devicechannelsbinding.h"

using namespace elekdom::oplink::core::observable;
using namespace elekdom::oplink::core;

OperationDevice::OperationDevice()
{

}

OperationDevice::~OperationDevice()
{

}

void OperationDevice::setDevice(QSharedPointer<infrastructure::Device> device)
{
    m_device = device;
}

QSharedPointer<infrastructure::Device> OperationDevice::device()
{
    return m_device;
}

void OperationDevice::bindChannels(const infrastructure::DeviceChannelsBinding &deviceChannelsBinding)
{
    for (int i = 0; i < deviceChannelsBinding.size(); i++)
    {
        bindChannel(i, deviceChannelsBinding.at(i));
    }
}

void OperationDevice::setChannelValue(int idx, QVariant value)
{
    QspOperationDeviceProperty pro{m_channels[idx]};

    if (pro.isNull())
    {
        pfWarning1(logChannel()) << QObject::tr("Canal %1 non associé pour l'observable %2").arg(idx).arg(name());
    }
    else
    {
        pro->changeValue(value);
    }
}

bool OperationDevice::getChannelIdx(const PropertyName &propertyName, int &idx)
{
    bool ret{m_reverseChannels.contains(propertyName)};

    if (ret)
    {
        idx = m_reverseChannels.value(propertyName);
    }

    return ret;
}

bool OperationDevice::hasChannel(int idx)
{
    return idx < m_channels.size();
}

void OperationDevice::bindChannel(int index, const PropertyName &pname)
{
    QspProperty prop{property(pname)};

    if (prop.isNull())
    {
        pfWarning1(logChannel()) << QObject::tr("Pas de propriété %1 pour l'observable %2").arg(pname, name());
    }
    else
    {
        QspOperationDeviceProperty odProp{prop.dynamicCast<OperationDeviceProperty>()};

        if (odProp.isNull())
        {
            pfWarning1(logChannel()) << QObject::tr("Impossible de retrouver la propriété %1 pour l'observable %2").arg(pname, name());
        }
        else
        {
            if (index > m_channels.size() - 1)
            {
                m_channels.resize(index + 1);
            }
            m_channels[index] = odProp;
            m_reverseChannels[odProp->name()] = index;
        }
    }
}
