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
#include "observablemodelregister_forward.h"

class ObservableModelRegisterFactory : public plugframe::BundleFactory
{
public:
    ObservableModelRegisterFactory();
    ~ObservableModelRegisterFactory() override;

protected:
    virtual ModelRegisterService *createModelRegisterService(plugframe::BundleImplementation *implementation);
    virtual ObservableBuilderService *createObservableBuilderService(plugframe::BundleImplementation *implementation);
    virtual plugframe::ServiceImplementationInterface *createServiceImplementation(plugframe::BundleImplementation *implementation,
                                                                                   const QString& sName,
                                                                                   const QString& serviceVersion) override;
};

#endif // OBSERVABLEMODELREGISTERFACTORY_H
