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


#ifndef OBSERVABLEMODELREGISTERPLUGIN_H
#define OBSERVABLEMODELREGISTERPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/modelregisterserviceinterface.h"
#include "service-int/observablebuilderserviceinterface.h"
#include "observablemodelregister_forward.h"
#include "olcore-backend-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace observablemodelregister
{
namespace plugin
{

class ObservableModelRegisterPlugin : public plugframe::core::plugin::Plugin,
                                         public service::ModelRegisterServiceInterface,
                                         public service::ObservableBuilderServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.oplink.observablemodelregister.plugin" FILE "../oplinkB-observablemodelregisterbundle.json")
    Q_INTERFACES(elekdom::plugframe::core::plugin::BundleInterface
                 elekdom::oplink::observablemodelregister::service::ModelRegisterServiceInterface
                 elekdom::oplink::observablemodelregister::service::ObservableBuilderServiceInterface)

public:
    ObservableModelRegisterPlugin();
    ~ObservableModelRegisterPlugin() override;

protected: // SmfPlugin
    plugframe::core::bundle::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // QspModelRegisterServiceInterface
    bool addPropertyModel(core::model::QspObservablePropertyModel model) override;
    core::model::QspObservablePropertyModel getPropertyModel(core::model::PropertyModelName id) override;
    bool addProcessorModel(core::model::QspCommandProcessorModel model) override;
    core::model::QspCommandProcessorModel getProcessorModel(core::model::ProcessorModelName id) override;
    bool addObservableModel(core::model::QspObservableModel model) override;

protected: // GacObservableBuilderServiceInterface
    core::observable::QspObservableBuilder buildObservable(core::model::QspObservableBuilderArgs builderargs) override;

private:
    service::QspModelRegisterService     m_modelRegisterServiceImpl;
    service::QspObservableBuilderService m_observableBuilderServiceImpl;
};

}//plugin
}//observablemodelregister
}//gac
}//elekdom
#endif // OBSERVABLEMODELREGISTERPLUGIN_H
