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

#include "enoceaninfrastructure.h"
#include "enoceaninfrastructurelogchannel.h"
#include "loader/enoceaninfrastructureoperatingloader.h"
#include "packet/esp3packet.h"
#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"
#include "packet/format/sentformat/esp3sentpacketformat.h"

EnoceanInfrastructure::EnoceanInfrastructure():
    oplink::Infrastructure{s_EnoceanLogChannel, "ENOCEAN"}
{
    qRegisterMetaType<QspEsp3Packet>("elekdom::oplink::enocean::QspEsp3Packet");
    qRegisterMetaType<QspEepTelegramFormat>("elekdom::oplink::enocean::QspEepTelegramFormat");
    qRegisterMetaType<QspEsp3SentPacketFormat>("elekdom::oplink::enocean::QspEsp3SentPacketFormat");
}

EnoceanInfrastructure::~EnoceanInfrastructure()
{

}

oplink::InfrastructureLoader *EnoceanInfrastructure::createOperatingLoader(const QString& logChannel)
{
    return new EnoceanInfrastructureOperatingLoader(logChannel, *this);
}

oplink::InfrastructureLoader *EnoceanInfrastructure::createSetupLoader(const QString& logChannel)
{
    Q_UNUSED(logChannel)

    //TODO
    //...

    return nullptr;
}


