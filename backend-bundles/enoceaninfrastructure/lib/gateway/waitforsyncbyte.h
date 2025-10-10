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


#ifndef WAITFORSYNCBYTE_H
#define WAITFORSYNCBYTE_H

#include "esp3serialreceiverstate.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class WaitForSyncByte : public Esp3SerialReceiverState
{
public:
    WaitForSyncByte(Esp3PacketSerialReceiver& receiver);
    ~WaitForSyncByte() override;

protected:
   void input(quint8 byte) override;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // WAITFORSYNCBYTE_H
