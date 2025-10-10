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


#ifndef F60201EEP_H
#define F60201EEP_H

#include "f602eep.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class F60201Eep : public F602Eep
{
public:
    F60201Eep(const core::infrastructure::DeviceId& id,
              core::infrastructure::DeviceHook& deviceHook);
    ~F60201Eep() override;

protected:
    bool processTelegram() override;
};

}//namespace bundleTemplate
}//namespace hac
}//namespace enocean

#endif // F60201EEP_H
