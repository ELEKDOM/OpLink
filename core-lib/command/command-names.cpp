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


#include "command-names.h"

using namespace elekdom::oplink::core::command;

const CommandName CommandNames::SYNCHRONIZE{QStringLiteral("synchronize")};
const CommandName CommandNames::SET{QStringLiteral("set")};
const CommandName CommandNames::ENERGY{QStringLiteral("energy")};
const CommandName CommandNames::POWER{QStringLiteral("power")};

const CommandArg CommandArgs::ON{QStringLiteral("on")};
const CommandArg CommandArgs::OFF{QStringLiteral("off")};
const CommandArg CommandArgs::COMFORT{QStringLiteral("comfort")};
const CommandArg CommandArgs::COMFORT_1{QStringLiteral("comfort_1")};
const CommandArg CommandArgs::COMFORT_2{QStringLiteral("comfort_2")};
const CommandArg CommandArgs::ECO{QStringLiteral("eco")};
const CommandArg CommandArgs::NOFROST{QStringLiteral("nofrost")};
