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


#ifndef D201EEP_H
#define D201EEP_H

#include "d2eep.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class D201Eep : public D2Eep
{
public:
    D201Eep(const core::infrastructure::DeviceId& id,
            core::infrastructure::DeviceHook& deviceHook);
    ~D201Eep() override;

protected:
    bool msgCmd04(QspD201TelegramFormat& telFormat, bool& processed);// Actuator Status Response
    bool msgCmd07(QspD201TelegramFormat& telFormat, bool& processed);// Actuator Measurement Response
    bool msgCmd0A(QspD201TelegramFormat& telFormat, bool& processed);// Actuator Pilot Wire Mode Response
};

}//namespace bundleTemplate
}//namespace oplink
}//namespace enocean

#endif // D201EEP_H
