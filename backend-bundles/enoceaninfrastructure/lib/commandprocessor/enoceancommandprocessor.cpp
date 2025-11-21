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
#include "command/command.h"
#include "commandprocessor/enoceancommandprocessor.h"
#include "device/enoceanequipmentprofile.h"
#include "enoceaninfrastructurelogchannel.h"
#include "packet/format/sentformat/eepcommandformat/eepcommandformat.h"

EnoceanCommandProcessor::EnoceanCommandProcessor(const oplink::QspDevice &device,
                                                 EepCommandFormat *sentCommandFormat):
    oplink::DeviceCommandProcessor{s_EnoceanLogChannel, device},
    m_sentCommandFormat{sentCommandFormat}
{

}

EnoceanCommandProcessor::~EnoceanCommandProcessor()
{

}

void EnoceanCommandProcessor::processDeviceCmd(oplink::QspCommand order)
{
    m_sentCommandFormat->newPacket();
    if (completePacket(order))
    {
        sendPacket();
    }
    else
    {
        pfWarning4(logChannel()) << QObject::tr("Commande erronnée, non envoyée : %1 %2 %3 %4").arg(order->name(),
                                                                                                     order->observable(),
                                                                                                     order->property(),
                                                                                                     order->value().toString());
    }
}

void EnoceanCommandProcessor::sendPacket()
{
    const oplink::QspDevice& Device{device()};
    qint32 destinationId{(Device->id()).toInt(nullptr, 16)};

    m_sentCommandFormat->insertDestinationId(destinationId);

    const QspEnoceanEquipmentProfile& eep{Device.dynamicCast<EnoceanEquipmentProfile>()};

    eep->sendEepCommand(m_sentCommandFormat);
}
