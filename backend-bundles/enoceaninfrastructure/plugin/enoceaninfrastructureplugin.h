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


#ifndef ENOCEANINFRASTRUCTUREPLUGIN_H
#define ENOCEANINFRASTRUCTUREPLUGIN_H

#include "abstract_infrastructure/plugin/infrastructureplugin.h"
#include "service-int/infrastructurecontrolserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{
namespace plugin
{

class EnoceanInfrastructurePlugin : public oplink::core::infrastructure::plugin::InfrastructurePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.oplink.enocean.plugin" FILE "../oplinkB-enoceaninfrastructurebundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface
                 elekdom::oplink::core::infrastructure::service::InfrastructureControlServiceInterface)

public:
    EnoceanInfrastructurePlugin();
    virtual ~EnoceanInfrastructurePlugin();

protected:
    virtual plugframe::core::bundle::Bundle4PluginInterface *createImplementation();
};

}//namespace plugin
}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ENOCEANINFRASTRUCTUREPLUGIN_H
