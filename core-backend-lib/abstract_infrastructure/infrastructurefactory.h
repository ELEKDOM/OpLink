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


#ifndef INFRASTRUCTUREFACTORY_H
#define INFRASTRUCTUREFACTORY_H

#include <QString>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "factory/bundlefactory.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{
namespace factory
{

class OLCORE_BACKEND_LIB_EXPORT InfrastructureFactory : public plugframe::core::bundle::BundleFactory
{
public:
    InfrastructureFactory();
    ~InfrastructureFactory() override;

protected:
    virtual service::InfrastructureControlService *createDeviceInfrastructureControlService(plugframe::core::bundle::BundleImplementation *implementation);
    plugframe::core::service::ServiceImplementationInterface *createServiceImplementation(plugframe::core::bundle::BundleImplementation *implementation,
                                                                         const QString& sName,
                                                                         const QString& serviceVersion) override;

};

}//namespace factory
}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // INFRASTRUCTUREFACTORY_H
