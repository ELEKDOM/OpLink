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
#include "device/f60101eep.h"
#include "packet/format/receivedformat/eeptelegram/f601telegramformat.h"

using namespace elekdom::oplink::enocean;

F60101Eep::F60101Eep(const core::infrastructure::DeviceId &id,
                     core::infrastructure::DeviceHook &deviceHook):
    F601Eep{id, deviceHook, new F601TelegramFormat}
{

}

F60101Eep::~F60101Eep()
{

}

bool F60101Eep::processTelegram()
{
    bool ret{false};

    QspF601TelegramFormat formatF60101{(msgFormat()).dynamicCast<F601TelegramFormat>()};

    // TODO
    // ...
    // Faire des essais avec des interupteurs afin d'interpreter les messages
     pfWarning7(logChannel()) << QObject::tr("F60101Eep processTelegram : data byte = 0x") << Qt::hex << formatF60101->dataByte();

    return ret;
}
