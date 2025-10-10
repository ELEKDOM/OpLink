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


#include "a5telegramformat.h"

using namespace elekdom::oplink::enocean;

A5TelegramFormat::A5TelegramFormat() {}

A5TelegramFormat::~A5TelegramFormat()
{

}

quint8 A5TelegramFormat::db_3()
{
    const quint8 *data{rawData()};
    return data[1]; // data[0] is RORG
}

quint8 A5TelegramFormat::db_2()
{
    const quint8 *data{rawData()};
    return data[2]; // data[0] is RORG
}

quint8 A5TelegramFormat::db_1()
{
    const quint8 *data{rawData()};
    return data[3]; // data[0] is RORG
}

quint8 A5TelegramFormat::db_0()
{
    const quint8 *data{rawData()};
    return data[4]; // data[0] is RORG
}
