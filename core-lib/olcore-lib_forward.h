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


#ifndef OLCORELIB_FORWARD_H
#define OLCORELIB_FORWARD_H

#include <QSharedPointer>

namespace elekdom
{
namespace oplink
{
namespace core
{
    namespace tcp
    {
        class SigninMessage;
        class SigninReplyMessage;
        class SessionStartedMessage;
        class SignoutMessage;
        class DownloadConfigMessage;
        class ReadyMessage;
        class DownloadConfigReplyMessage;
        class StateValueMessage;
        class SubmitOrderMessage;
    }

    namespace remote
    {
        class SessionConfDocument;

        using QspSessionConfDocument = QSharedPointer<SessionConfDocument>;
    }

    namespace virtualequipment
    {
        class VirtualEquipmentConfDocument;
        class VirtualEquipmentLoaderHook;

        using QspVirtualEquipmentConfDocument = QSharedPointer<VirtualEquipmentConfDocument>;
    }

    namespace heatingmanager
    {
        class HeatingManagerLoaderHook;
        class HeatingManagerConfDocument;

        using QspHeatingManagerConfDocument = QSharedPointer<HeatingManagerConfDocument>;
    }

}//namespace core
}//namespace oplink
}//namespace elekdom
#endif // OLCORELIB_FORWARD_H
