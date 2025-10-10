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


#ifndef COMMONCOMMANDFORMAT_H
#define COMMONCOMMANDFORMAT_H

#include "packet/format/sentformat/esp3sentpacketformat.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class CommonCommandFormat : public Esp3SentPacketFormat
{
private:
    quint8 m_cmd;

public:
    CommonCommandFormat(quint16 commonCommandDataSize, quint8 optionalLenght, quint8 cmd);
    ~CommonCommandFormat() override;

protected:
    void fillInData() override;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // COMMONCOMMANDFORMAT_H
