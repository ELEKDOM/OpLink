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


#include "gacengineplugin.h"
#include "serverengine.h"
#include "observableservice.h"

using namespace elekdom::oplink::engine::plugin;
using namespace elekdom::oplink::core;
using namespace elekdom::plugframe::core;

GacEnginePlugin::GacEnginePlugin()
{

}

elekdom::oplink::engine::plugin::GacEnginePlugin::~GacEnginePlugin()
{

}

bundle::Bundle4PluginInterface *GacEnginePlugin::createImplementation()
{
    return new bundle::ServerEngine;
}

void GacEnginePlugin::bindServicesImplementations()
{
    plugframe::core::service::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(ObservableServiceInterface::serviceName());
    m_observableServiceImpl = serviceImplementationItf.dynamicCast<service::ObservableService>();
}

bool GacEnginePlugin::submitOrder(core::command::StrOrder command)
{
    return m_observableServiceImpl->submitOrder(command);
}

bool GacEnginePlugin::subscribe(core::observable::ObservableName observableName,
                                core::observable::ObservableSubscriber *subscriber)
{
    return m_observableServiceImpl->subscribe(observableName, subscriber);
}

bool GacEnginePlugin::unsubscribe(core::observable::ObservableName observableName,
                                  core::observable::ObservableSubscriber *subscriber)
{
    return m_observableServiceImpl->unsubscribe(observableName, subscriber);
}

bool GacEnginePlugin::propertyValue(core::observable::ObservableName observableName,
                                    core::observable::PropertyName propertyName,
                                    QVariant& value)
{
    return m_observableServiceImpl->propertyValue(observableName, propertyName, value);
}

observable::QspProperty GacEnginePlugin::property(core::observable::ObservableName observableName, core::observable::PropertyName propertyName)
{
    return m_observableServiceImpl->property(observableName,propertyName);
}

