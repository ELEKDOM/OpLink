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


#ifndef MODELREGISTERSERVICE_H
#define MODELREGISTERSERVICE_H

#include "observablemodelregisterserviceimplementation.h"
#include "olcore-backend-lib_forward.h"
#include "model/modelnames.h"

using namespace elekdom::plugframe::core;

namespace elekdom
{
namespace oplink
{
namespace observablemodelregister
{
namespace service
{

class ModelRegisterService : public ObservableModelRegisterServiceImplementation
{
public:
    ModelRegisterService(plugframe::core::bundle::BundleImplementation *implementation);
    ~ModelRegisterService() override;

public:
    virtual bool addPropertyModel(core::model::QspObservablePropertyModel model);
    virtual core::model::QspObservablePropertyModel getPropertyModel(core::model::PropertyModelName id);
    virtual bool addProcessorModel(core::model::QspCommandProcessorModel model);
    virtual core::model::QspCommandProcessorModel getProcessorModel(core::model::ProcessorModelName id);
    virtual bool addObservableModel(core::model::QspObservableModel model);

protected:
    QString serviceName() override;
};

}//namespace service
}//namespace observablemodelregister
}//namespace oplink
}//namespace elekdom

#endif // MODELREGISTERSERVICE_H
