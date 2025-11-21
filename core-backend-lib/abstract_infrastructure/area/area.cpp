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

#include "area.h"
#include "logger/pflog.h"

oplink::Area::Area(const QString& logChannel,
                   const QString& areaName,
                   QObject *parent):
    QObject{parent},
    plugframe::Loggable{logChannel},
    m_areaName{areaName}
{

}

oplink::Area::~Area()
{

}

void oplink::Area::setGateway(oplink::AreaGateway *gateway)
{
    m_gateway.reset(gateway);
}

bool oplink::Area::addDevice(const oplink::QspDevice &newDevice)
{
    bool ret{false};

    if (m_devices.contains(newDevice->id()))
    {
        pfWarning1(logChannel()) << tr("device id %1 déjà inséré dans cette zone!").arg(newDevice->id());
    }
    else
    {
        ret = true;
        m_devices.insert(newDevice->id(), newDevice);
    }

    return ret;
}

oplink::QspDevice oplink::Area::getDevice(const oplink::DeviceId &id)
{
    oplink::QspDevice ret;

    if (m_devices.contains(id))
    {
        ret = m_devices.value(id);
    }
    return ret;
}

void oplink::Area::recoverDevicesState()
{
    foreach (oplink::QspDevice device, m_devices)
    {
        device->recoverState();
    }
}
