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

#include "logger/pflog.h"
#include "abstract_infrastructure/device/device.h"
#include "area/enoceanoperatingdevicearea.h"
#include "device/enoceanequipmentprofile.h"
#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"

EnoceanOperatingDeviceArea::EnoceanOperatingDeviceArea(const QString& logChannel,
                                                       const QString& areaName,
                                                       QObject *parent):
    EnoceanDeviceArea{logChannel,
                      areaName,
                      parent}
{

}

EnoceanOperatingDeviceArea::~EnoceanOperatingDeviceArea()
{

}

void EnoceanOperatingDeviceArea::onErp1PacketReceived(QspEepTelegramFormat erp1PacketFormat)
{
    QString idStr{erp1PacketFormat->getSenderId()};
    oplink::QspDevice device{getDevice(idStr)};

    if (!device.isNull())
    {
        QspEnoceanEquipmentProfile eep{device.dynamicCast<EnoceanEquipmentProfile>()};

        eep->processTelegram(erp1PacketFormat->associatedPacket());
    }
    else
    {
        pfWarning7(logChannel()) << tr("Area : identifiant de device non déclaré, ") <<  idStr;
    }
}
