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


#ifndef GACENGINEPLUGIN_H
#define GACENGINEPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/observableserviceinterface.h"
#include "serverengine_forward.h"

namespace elekdom
{
namespace oplink
{
namespace engine
{
namespace plugin
{

class GacEnginePlugin : public plugframe::core::plugin::Plugin,
                        public service::ObservableServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.oplink.engine.plugin" FILE "../oplinkB-enginebundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface
                 elekdom::oplink::engine::service::ObservableServiceInterface)

private:
    service::QspObservableService m_observableServiceImpl;

public:
    GacEnginePlugin();
    ~GacEnginePlugin() override;

protected:
    plugframe::core::bundle::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected:
    bool submitOrder(core::command::StrOrder command) override;
    bool subscribe(core::observable::ObservableName observableName,
                   core::observable::ObservableSubscriber *subscriber) override;
    bool unsubscribe(core::observable::ObservableName observableName,
                     core::observable::ObservableSubscriber *subscriber) override;
    bool propertyValue(core::observable::ObservableName observableName,
                       core::observable::PropertyName propertyName,
                       QVariant& value) override;
    core::observable::QspProperty property(core::observable::ObservableName observableName,
                                           core::observable::PropertyName propertyName) override;
};

}//namespace plugin
}//namespace engine
}//namespace oplink
}//namespace elekdom

#endif // GACENGINEPLUGIN_H
