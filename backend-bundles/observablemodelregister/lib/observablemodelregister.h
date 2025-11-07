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

#ifndef OBSERVABLEMODELREGISTER_H
#define OBSERVABLEMODELREGISTER_H

#include "bundle/bundleimplementation.h"
#include "model/modelnames.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "model/observable/observablemodel.h"

class ObservableModelRegister : public plugframe::BundleImplementation
{
private:
    QHash<const oplink::PropertyModelName,oplink::QspObservablePropertyModel> m_propertyModels; // properties definition (models) store.
    QHash<const oplink::ProcessorModelName,oplink::QspCommandProcessorModel>  m_processorModels;
    QHash<const oplink::ObservableModelName,oplink::QspObservableModel>       m_observableModels; // observables definition (models) store. Key is model's name

public:
    ObservableModelRegister();
    ~ObservableModelRegister() override;

public:
    oplink::QspObservableModel getObservableModel(const oplink::ObservableModelName& modelName);

public: // for class EdModelRegisterService;
    bool addPropertyModel(oplink::QspObservablePropertyModel model);
    oplink::QspObservablePropertyModel getPropertyModel(oplink::PropertyModelName id);
    bool addProcessorModel(oplink::QspCommandProcessorModel model);
    oplink::QspCommandProcessorModel getProcessorModel(oplink::ProcessorModelName id);
    bool addObservableModel(oplink::QspObservableModel model);

public: // for class EdObservableBuilderService
    oplink::QspObservableBuilder buildObservable(oplink::QspObservableBuilderArgs builderargs);

protected:
    plugframe::BundleFactory* createFactory() override;
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;
};

#endif // OBSERVABLEMODELREGISTER_H
