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

#ifndef MESSAGE_H
#define MESSAGE_H

#include "abstract_network_tcp/common/tcpchannelmessage.h"
#include "olcore-lib_export.h"

namespace oplink
{
class OLCORE_LIB_EXPORT Message : public plugframe::TcpChannelMessage
{
public:
    Message(quint16 msgType);
    ~Message() override;
};
}//namespace oplink
#endif // MESSAGE_H
