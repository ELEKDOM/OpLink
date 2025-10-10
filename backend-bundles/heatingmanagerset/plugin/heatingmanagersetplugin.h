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


#ifndef HEATINGMANAGERSETPLUGIN_H
#define HEATINGMANAGERSETPLUGIN_H

#include "abstract_virtualequipementset/plugin/virtualequipmentsetplugin.h"
#include "service-int/virtualequipmentsetserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace heatingmanagerset
{
namespace plugin
{

class HeatingManagerSetPlugin : public core::virtualequipmentset::plugin::VirtualEquipmentSetPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.oplink.heatingmanagerset.plugin" FILE "../oplinkB-heatingmanagersetbundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface
                 elekdom::oplink::core::virtualequipmentset::service::VirtualEquipmentSetServiceInterface)

public:
    HeatingManagerSetPlugin();
    ~HeatingManagerSetPlugin() override;

protected:
    plugframe::core::bundle::Bundle4PluginInterface *createImplementation() override;
};

}//namespace plugin
}//namespace heatingmanagerset
}//namespace oplink
}//namespace elekdom

#endif // HEATINGMANAGERSETPLUGIN_H
