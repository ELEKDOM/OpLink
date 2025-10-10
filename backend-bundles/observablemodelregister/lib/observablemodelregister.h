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
#include "olcore-backend-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace observablemodelregister
{
namespace bundle
{

class ObservableModelRegister : public plugframe::core::bundle::BundleImplementation
{
private:
    QHash<const core::model::PropertyModelName,core::model::QspObservablePropertyModel> m_propertyModels; // properties definition (models) store.
    QHash<const core::model::ProcessorModelName,core::model::QspCommandProcessorModel>  m_processorModels;
    QHash<const core::model::ObservableModelName,core::model::QspObservableModel>       m_observableModels; // observables definition (models) store. Key is model's name

public:
    ObservableModelRegister();
    ~ObservableModelRegister() override;

public:
    core::model::QspObservableModel getObservableModel(const core::model::ObservableModelName& modelName);

public: // for class EdModelRegisterService;
    bool addPropertyModel(core::model::QspObservablePropertyModel model);
    core::model::QspObservablePropertyModel getPropertyModel(core::model::PropertyModelName id);
    bool addProcessorModel(core::model::QspCommandProcessorModel model);
    core::model::QspCommandProcessorModel getProcessorModel(core::model::ProcessorModelName id);
    bool addObservableModel(core::model::QspObservableModel model);

public: // for class EdObservableBuilderService
    core::observable::QspObservableBuilder buildObservable(core::model::QspObservableBuilderArgs builderargs);

protected:
    plugframe::core::bundle::BundleFactory* createFactory() override;
    plugframe::core::plugin::ServiceInterface *qtServiceInterface(const QString& sName) override;
};

}//namespace bundle
}//namespace observablemodelregister
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEMODELREGISTER_H
