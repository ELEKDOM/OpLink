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


#ifndef OBSERVABLEMODELLOADER_H
#define OBSERVABLEMODELLOADER_H

#include <QDomDocument>
#include "bundle/longstartbundleimplementation.h"
#include "service-int/modelregisterserviceinterface.h"
#include "model/modelnames.h"
#include "observable/observablenames.h"
#include "command/command-names.h"
#include "observablemodelloader_forward.h"
#include "pfcore-lib_forward.h"

using namespace elekdom::plugframe::core::bundle;

namespace elekdom
{
namespace oplink
{
namespace observablemodelloader
{
namespace bundle
{

class ObservableModelLoader : public plugframe::core::bundle::LongStartBundleImplementation
{
public:
    ObservableModelLoader();
    ~ObservableModelLoader() override;

public:
    QSharedPointer<ObservableModelLoaderEmitter> emitter();
    observablemodelregister::service::ModelRegisterServiceInterface *modelRegisterService();

public:
    bool nextPropertyModelDeclaration(quint16 idx,
                                      core::model::PropertyModelName& modelName,
                                      core::observable::PropertyName& propertyName,
                                      core::observable::PropertyType& propertyClassName,
                                      QVariant::Type& valueType);
    bool nextProcessorModelDeclaration(quint16 idx,
                                       core::model::ProcessorModelName& modelName,
                                       core::command::CommandName& commandName,
                                       core::observable::ProcessorType& processorClassName);
    bool nextObservableModelDeclaration(quint16 idx,
                                        core::model::ObservableModelName& modelName,
                                        core::observable::ObservableType& observableClassName,
                                        QStringList& propertyModelRefs,
                                        QStringList& processorModelRefs);

protected:
    BundleFactory* createFactory() override;
    void _start(QspBundleContext bundleContext) override;
    PF_qtServiceInterface_DECL

private:
    void startModelsLoading();
    bool loadModelDeclarations();

private:
    QDomDocument m_modelDeclarations;
    QDomNodeList m_propertyModelNodes;
    QDomNodeList m_processorModelNodes;
    QDomNodeList m_observableModelNodes;
};

}//namespace bundle
}//namespace observablemodelloader
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEMODELLOADER_H
