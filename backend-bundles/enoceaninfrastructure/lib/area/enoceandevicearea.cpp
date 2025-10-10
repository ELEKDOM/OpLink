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


#include "abstract_infrastructure/device/device.h"
#include "logger/pflog.h"
#include "enoceaninfrastructurelogchannel.h"
#include "area/enoceandevicearea.h"
#include "gateway/enoceangateway.h"
#include "gateway/enoceangatewaymode.h"
#include "device/enoceanequipmentprofile.h"

using namespace elekdom::oplink::enocean;

EnoceanDeviceArea::EnoceanDeviceArea(const QString& logChannel,
                                     const QString& areaName,
                                     QObject *parent):
    core::infrastructure::Area{logChannel,
                                  areaName,
                                  parent},
    m_devicesLoaded{false},
    m_usb300IdRecovered{false}
{

}

EnoceanDeviceArea::~EnoceanDeviceArea()
{

}

void EnoceanDeviceArea::setGateway(core::infrastructure::AreaGateway *gateway)
{
    Area::setGateway(gateway);

    EnoceanGateway *enoceanGateway{dynamic_cast<EnoceanGateway*>(gateway)};
    bool ok = connect(enoceanGateway, SIGNAL(erp1PacketReceived(QspEepTelegramFormat)), SLOT(onErp1PacketReceived(QspEepTelegramFormat)));
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanDeviceArea connect signal erp1PacketReceived : échec");
    }

    ok = connect(this, SIGNAL(initializeUsb300BaseId()), enoceanGateway, SLOT(onInitializeUsb300BaseId()), Qt::QueuedConnection);
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanDeviceArea connect signal initializeUsb300BaseId : échec");
    }

    // Devices' states are synchronised at startup !
    EnoceanGatewayMode *enoceanGatewayMode{enoceanGateway->mode()};
    ok = connect(enoceanGatewayMode, SIGNAL(usb300IdRecovered()), SLOT(onUsb300IdRecovered()));
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanDeviceArea connect signal usb300IdRecovered : échec");
    }
    ok = connect(this, SIGNAL(devicesLoaded()), SLOT(onDevicesLoaded()));
    if (!ok)
    {
        pfWarning1(s_EnoceanLogChannel) << tr("--EnoceanDeviceArea connect signal devicesLoaded : échec");
    }

    // Recover baseId;
    emit initializeUsb300BaseId();
}

bool EnoceanDeviceArea::addDevice(const core::infrastructure::QspDevice &newDevice)
{
    bool ret{Area::addDevice(newDevice)};

    if (ret)
    {
        EnoceanGateway *enoceanGateway{dynamic_cast<EnoceanGateway*>(gateway())};
        QspEnoceanEquipmentProfile eep{newDevice.dynamicCast<EnoceanEquipmentProfile>()};

        eep->setEnoceanGateway(enoceanGateway);
    }

    return ret;
}

void EnoceanDeviceArea::onDevicesLoaded()
{
    m_devicesLoaded = true;
    if (m_usb300IdRecovered)
    {
        recoverDevicesState();
        m_devicesLoaded = m_usb300IdRecovered = false;
    }
}

void EnoceanDeviceArea::onUsb300IdRecovered()
{
    m_usb300IdRecovered = true;
    if (m_devicesLoaded)
    {
        recoverDevicesState();
        m_devicesLoaded = m_usb300IdRecovered = false;
    }
}
