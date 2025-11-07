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

#include <QSharedPointer>
#include "observablemodelregisterserviceimplementation.h"
#include "model/modelnames.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablemodel.h"

class ModelRegisterService : public ObservableModelRegisterServiceImplementation
{
public:
    ModelRegisterService(plugframe::BundleImplementation *implementation);
    ~ModelRegisterService() override;

public:
    virtual bool addPropertyModel(oplink::QspObservablePropertyModel model);
    virtual oplink::QspObservablePropertyModel getPropertyModel(oplink::PropertyModelName id);
    virtual bool addProcessorModel(oplink::QspCommandProcessorModel model);
    virtual oplink::QspCommandProcessorModel getProcessorModel(oplink::ProcessorModelName id);
    virtual bool addObservableModel(oplink::QspObservableModel model);

protected:
    QString serviceName() override;
};
using QspModelRegisterService = QSharedPointer<ModelRegisterService>;
#endif // MODELREGISTERSERVICE_H
