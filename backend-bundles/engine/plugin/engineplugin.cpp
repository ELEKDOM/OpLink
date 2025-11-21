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

#include "engineplugin.h"
#include "serverengine.h"
#include "observableservice.h"

EnginePlugin::EnginePlugin()
{

}

EnginePlugin::~EnginePlugin()
{

}

plugframe::Bundle4PluginInterface *EnginePlugin::createImplementation()
{
    return new ServerEngine;
}

void EnginePlugin::bindServicesImplementations()
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;

    serviceImplementationItf = implementation()->getServiceImplementation(ObservableServiceInterface::serviceName());
    m_observableServiceImpl = serviceImplementationItf.dynamicCast<ObservableService>();
}

bool EnginePlugin::submitOrder(oplink::StrOrder command)
{
    return m_observableServiceImpl->submitOrder(command);
}

bool EnginePlugin::subscribe(oplink::ObservableName observableName,
                             oplink::ObservableSubscriber *subscriber)
{
    return m_observableServiceImpl->subscribe(observableName, subscriber);
}

bool EnginePlugin::unsubscribe(oplink::ObservableName observableName,
                               oplink::ObservableSubscriber *subscriber)
{
    return m_observableServiceImpl->unsubscribe(observableName, subscriber);
}

bool EnginePlugin::propertyValue(oplink::ObservableName observableName,
                                 oplink::PropertyName propertyName,
                                 QVariant& value)
{
    return m_observableServiceImpl->propertyValue(observableName, propertyName, value);
}

oplink::QspProperty EnginePlugin::property(oplink::ObservableName observableName, oplink::PropertyName propertyName)
{
    return m_observableServiceImpl->property(observableName,propertyName);
}

