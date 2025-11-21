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
#include "model/modelnames.h"
#include "model/observable/observablemodel.h"

namespace oplink
{
class ModelRegisterServiceInterface : public plugframe::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("ModelRegisterServiceInterface");}

public:
    ~ModelRegisterServiceInterface() override {}

public:
    virtual bool addPropertyModel(oplink::QspObservablePropertyModel model) = 0;
    virtual oplink::QspObservablePropertyModel getPropertyModel(oplink::PropertyModelName id) = 0;
    virtual bool addProcessorModel(oplink::QspCommandProcessorModel model) = 0;
    virtual oplink::QspCommandProcessorModel getProcessorModel(oplink::ProcessorModelName id) = 0;
    virtual bool addObservableModel(oplink::QspObservableModel model) = 0;
};
}//namespace oplink

#define QspModelRegisterService_iid "oplink.ModelRegisterServiceInterface"
Q_DECLARE_INTERFACE(oplink::ModelRegisterServiceInterface, QspModelRegisterService_iid)

#endif // MODELREGISTERSERVICEINTERFACE_H
