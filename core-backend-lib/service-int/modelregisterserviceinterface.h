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


#ifndef MODELREGISTERSERVICEINTERFACE_H
#define MODELREGISTERSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "olcore-backend-lib_forward.h"
#include "model/modelnames.h"

using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace observablemodelregister
{
namespace service
{

class ModelRegisterServiceInterface : public plugframe::core::plugin::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("ModelRegisterServiceInterface");}

public:
    ~ModelRegisterServiceInterface() override {}

public:
    virtual bool addPropertyModel(core::model::QspObservablePropertyModel model) = 0;
    virtual core::model::QspObservablePropertyModel getPropertyModel(core::model::PropertyModelName id) = 0;
    virtual bool addProcessorModel(core::model::QspCommandProcessorModel model) = 0;
    virtual core::model::QspCommandProcessorModel getProcessorModel(core::model::ProcessorModelName id) = 0;
    virtual bool addObservableModel(core::model::QspObservableModel model) = 0;
};

}//service
}//namespace observablemodelregister
}//namespace oplink
}//namespace elekdom

#define QspModelRegisterService_iid "elekdom.oplink.observablemodelregister.service.ModelRegisterServiceInterface"
Q_DECLARE_INTERFACE(elekdom::oplink::observablemodelregister::service::ModelRegisterServiceInterface, QspModelRegisterService_iid)

#endif // MODELREGISTERSERVICEINTERFACE_H
