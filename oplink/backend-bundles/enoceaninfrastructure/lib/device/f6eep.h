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

#ifndef F6EEP_H
#define F6EEP_H

#include "enoceanequipmentprofile.h"

class F6Eep : public EnoceanEquipmentProfile
{
public:
    F6Eep(const oplink::DeviceId& id,
          oplink::DeviceHook& deviceHook,
          EepTelegramFormat *msgFormat);
    ~F6Eep() override;

protected:
    void recoverState() override;
};

#endif // F6EEP_H
