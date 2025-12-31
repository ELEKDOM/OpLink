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

#ifndef VIRTUALEQUIPMENTSETSERVICEINTERFACE_H
#define VIRTUALEQUIPMENTSETSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "worker/workerwatcher.h"

namespace oplink
{
class VirtualEquipmentSetServiceInterface : public plugframe::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("VirtualEquipmentSetServiceInterface");}

public:
    virtual ~VirtualEquipmentSetServiceInterface() {}

public:
    virtual const QString& getVirtualEquipmentSetName() = 0;

    // virtual equipments loading is realized by a worker task. At the end of loading, the workerwatcher is notified
    virtual bool startLoading(plugframe::WorkerWatcher *workerWatcher) = 0;

    virtual bool loadingFinished() = 0;
};
}//namespace oplink

#define OlVirtualEquipmentSetService_iid "oplink.VirtualEquipmentSetServiceInterface"
Q_DECLARE_INTERFACE(oplink::VirtualEquipmentSetServiceInterface, OlVirtualEquipmentSetService_iid)

#endif // VIRTUALEQUIPMENTSETSERVICEINTERFACE_H
