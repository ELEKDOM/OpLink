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

#ifndef D20112EEP_H
#define D20112EEP_H

#include "d201eep.h"

/* Actuator 2 Outputs Module */
class D20112Eep : public D201Eep
{
public:
    D20112Eep(const oplink::DeviceId& id,
              oplink::DeviceHook& deviceHook);
    ~D20112Eep() override;

protected:
    bool processTelegram() override;
};

#endif // D20112EEP_H
