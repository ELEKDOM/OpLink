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

#ifndef ENGINEPLUGIN_H
#define ENGINEPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/observableserviceinterface.h"
#include "observableservice.h"
class EnginePlugin : public plugframe::Plugin,
                     public oplink::ObservableServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "oplink.engine.plugin" FILE "../oplinkB-enginebundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 oplink::ObservableServiceInterface)

private:
    QspObservableService m_observableServiceImpl;

public:
    EnginePlugin();
    ~EnginePlugin() override;

protected:
    plugframe::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected:
    bool submitOrder(oplink::StrOrder command) override;
    bool subscribe(oplink::ObservableName observableName,
                   oplink::ObservableSubscriber *subscriber) override;
    bool unsubscribe(oplink::ObservableName observableName,
                     oplink::ObservableSubscriber *subscriber) override;
    bool propertyValue(oplink::ObservableName observableName,
                       oplink::PropertyName propertyName,
                       QVariant& value) override;
    oplink::QspProperty property(oplink::ObservableName observableName,
                                 oplink::PropertyName propertyName) override;
};
#endif // ENGINEPLUGIN_H
