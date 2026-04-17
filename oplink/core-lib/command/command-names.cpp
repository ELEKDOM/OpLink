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

const oplink::CommandName oplink::CommandNames::SYNCHRONIZE{QStringLiteral("synchronize")};
const oplink::CommandName oplink::CommandNames::SET{QStringLiteral("set")};
const oplink::CommandName oplink::CommandNames::ENERGY{QStringLiteral("energy")};
const oplink::CommandName oplink::CommandNames::POWER{QStringLiteral("power")};
const oplink::CommandName oplink::CommandNames::ROOM{QStringLiteral("room")};

const oplink::CommandArg oplink::CommandArgs::ON{QStringLiteral("on")};
const oplink::CommandArg oplink::CommandArgs::OFF{QStringLiteral("off")};
const oplink::CommandArg oplink::CommandArgs::COMFORT{QStringLiteral("comfort")};
const oplink::CommandArg oplink::CommandArgs::COMFORT_1{QStringLiteral("comfort1")};
const oplink::CommandArg oplink::CommandArgs::COMFORT_2{QStringLiteral("comfort2")};
const oplink::CommandArg oplink::CommandArgs::ECO{QStringLiteral("eco")};
const oplink::CommandArg oplink::CommandArgs::NOFROST{QStringLiteral("nofrost")};
const oplink::CommandArg oplink::CommandArgs::TRIGGER_MODE_ONDEMAND{QStringLiteral("ondemand")};
const oplink::CommandArg oplink::CommandArgs::TRIGGER_MODE_PLANNED{QStringLiteral("planned")};
