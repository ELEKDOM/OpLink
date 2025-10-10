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
#include "device/f60201eep.h"
#include "packet/format/receivedformat/eeptelegram/f602telegramformat.h"

using namespace elekdom::oplink::enocean;

F60201Eep::F60201Eep(const core::infrastructure::DeviceId& id,
                     core::infrastructure::DeviceHook& deviceHook):
    F602Eep{id, deviceHook, new F602TelegramFormat}
{

}

F60201Eep::~F60201Eep()
{

}

bool F60201Eep::processTelegram()
{
    QspF602TelegramFormat formatF60201{(msgFormat()).dynamicCast<F602TelegramFormat>()};
    quint8 channel;
    bool value;

    pfInfo7(logChannel()) << QObject::tr("F60201Eep processTelegram : data byte = 0x") << Qt::hex << formatF60201->dataByte() << " , status byte = 0x" << formatF60201->statusByte();

    if (formatF60201->buttonState(channel, value))
    {
        setChannelValue(channel, QVariant(value));
    }

    return true;
}
