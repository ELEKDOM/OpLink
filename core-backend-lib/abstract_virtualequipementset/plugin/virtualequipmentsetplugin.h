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


#ifndef VIRTUALEQUIPMENTSETPLUGIN_H
#define VIRTUALEQUIPMENTSETPLUGIN_H

#include "plugin/plugin.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "service-int/virtualequipmentsetserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipmentset
{
namespace plugin
{

class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetPlugin : public plugframe::core::plugin::Plugin,
                                                            public virtualequipmentset::service::VirtualEquipmentSetServiceInterface
{
public:
    VirtualEquipmentSetPlugin();
    ~VirtualEquipmentSetPlugin() override;

protected: // SmfPlugin
    void bindServicesImplementations() override;

protected: // VirtualEquipmentSetServiceInterface
    const QString& getVirtualEquipmentSetName() override;
    bool startLoading(plugframe::core::worker::WorkerWatcher *workerWatcher) override;
    bool loadingFinished() override;

private:
    virtualequipmentset::service::QspVirtualEquipmentSetService m_virtualEquipmentSetServiceImpl;
};

}//namespace plugin
}//namespace virtualequipmentset
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTSETPLUGIN_H
