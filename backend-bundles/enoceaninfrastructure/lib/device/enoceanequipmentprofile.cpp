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
#include "device/enoceanequipmentprofile.h"
#include "packet/format/sentformat/eepcommandformat/eepcommandformat.h"
#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"
#include "packet/esp3packet.h"
#include "gateway/enoceangateway.h"
#include "enoceaninfrastructurelogchannel.h"

using namespace elekdom::oplink::enocean;

EnoceanEquipmentProfile::EnoceanEquipmentProfile(const core::infrastructure::DeviceId& id,
                                                 core::infrastructure::DeviceHook& deviceHook,
                                                 EepTelegramFormat *msgFormat):
    core::infrastructure::Device{s_EnoceanLogChannel,
                              id,
                              deviceHook},
    m_msgFormat{msgFormat},
    m_gateway{nullptr}
{
}

EnoceanEquipmentProfile::~EnoceanEquipmentProfile()
{

}

void EnoceanEquipmentProfile::sendEepCommand(QspEepCommandFormat commandFormat)
{
    m_gateway->sendEepCommand(commandFormat);
}

void EnoceanEquipmentProfile::processTelegram(QspEsp3Packet& packet)
{
    m_msgFormat->setPacket(packet);
    if (!processTelegram())
    {
        pfWarning7(logChannel()) << QObject::tr("L'équipement %1 n'a pas traité le msg ").arg(id()) << m_msgFormat->getPacket()->logPacket();
    }
}
