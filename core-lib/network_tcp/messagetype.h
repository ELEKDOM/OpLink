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


#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include <QtGlobal>

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace tcp
{                                                         // Server     Client
enum class MessageType : quint16 {Signin,                 // I          O
                                  SiginReply,             // O          I
                                  Signout,                // I & O      O & I
                                  DownloadConfig,         // I          O
                                  DownloadConfigReply,    // O          I
                                  SessionStarted,         // O          I
                                  Ready,                  // I          O
                                  StateValue,             // O          I
                                  SubmitOrder};           // I          O

}//namespace tcp
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // MESSAGETYPE_H
