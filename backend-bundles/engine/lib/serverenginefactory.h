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


#ifndef SERVERENGINEFACTORY_H
#define SERVERENGINEFACTORY_H

#include "factory/bundlefactory.h"
#include "observableservice.h"
#include "serverengine.h"

namespace elekdom
{
namespace oplink
{
namespace engine
{
namespace factory
{

class ServerEngineFactory : public plugframe::core::bundle::BundleFactory
{
public:
    ServerEngineFactory();
    ~ServerEngineFactory() override;

protected:
    plugframe::core::service::ServiceImplementationInterface *createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation,
                                                                         const QString& sName,
                                                                         const QString& serviceVersion) override;
    plugframe::core::bundle::BundleListener *createBundleListener(plugframe::core::bundle::Bundle& myBundle) override;
    virtual service::ObservableService *createObservableService(plugframe::core::bundle::BundleImplementation *implementation);
};

}//namespace factory
}//namespace engine
}//namespace oplink
}//namespace elekdom

#endif // SERVERENGINEFACTORY_H
