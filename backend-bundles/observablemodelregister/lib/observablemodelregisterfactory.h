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


#ifndef OBSERVABLEMODELREGISTERFACTORY_H
#define OBSERVABLEMODELREGISTERFACTORY_H

#include "factory/bundlefactory.h"
#include "modelregisterservice.h"
#include "observablebuilderservice.h"
#include "observablemodelregister_forward.h"

namespace elekdom
{
namespace oplink
{
namespace observablemodelregister
{
namespace factory
{

class ObservableModelRegisterFactory : public plugframe::core::bundle::BundleFactory
{
public:
    ObservableModelRegisterFactory();
    ~ObservableModelRegisterFactory() override;

protected:
    virtual service::ModelRegisterService *createModelRegisterService(elekdom::plugframe::core::bundle::BundleImplementation *implementation);
    virtual service::ObservableBuilderService *createObservableBuilderService(elekdom::plugframe::core::bundle::BundleImplementation *implementation);
    virtual elekdom::plugframe::core::service::ServiceImplementationInterface *createServiceImplementation(elekdom::plugframe::core::bundle::BundleImplementation *implementation,
                                                                                 const QString& sName,
                                                                                 const QString& serviceVersion) override;
};

}//namespace factory
}//namespace observablemodelregister
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEMODELREGISTERFACTORY_H
