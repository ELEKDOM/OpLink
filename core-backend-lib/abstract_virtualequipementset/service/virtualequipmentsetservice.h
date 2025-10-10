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


#ifndef VIRTUALEQUIPMENTSETSERVICE_H
#define VIRTUALEQUIPMENTSETSERVICE_H

#include "olcore-backend-lib_export.h"
#include "service/serviceimplementation.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipmentset
{
namespace service
{

class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetService : public plugframe::core::service::ServiceImplementation
{
public:
    VirtualEquipmentSetService(plugframe::core::bundle::BundleImplementation *implementation);
    ~VirtualEquipmentSetService() override;

public:
    const QString& getVirtualEquipmentSetName();
    bool startLoading(plugframe::core::worker::WorkerWatcher *workerWatcher);
    bool loadingFinished();

protected:
    QString serviceName() override;
};

}//namespace service
}//namespace virtualequipmentset
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTSETSERVICE_H
