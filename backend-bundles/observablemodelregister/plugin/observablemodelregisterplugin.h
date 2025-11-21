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
#include "modelregisterservice.h"
#include "observablebuilderservice.h"

class ObservableModelRegisterPlugin : public plugframe::Plugin,
                                      public oplink::ModelRegisterServiceInterface,
                                      public oplink::ObservableBuilderServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "elekdom.oplink.observablemodelregister.plugin" FILE "../oplinkB-observablemodelregisterbundle.json")
    Q_INTERFACES(plugframe::BundleInterface
                 oplink::ModelRegisterServiceInterface
                 oplink::ObservableBuilderServiceInterface)
public:
    ObservableModelRegisterPlugin();
    ~ObservableModelRegisterPlugin() override;

protected: // Plugin
    plugframe::Bundle4PluginInterface *createImplementation() override;
    void bindServicesImplementations() override;

protected: // ModelRegisterServiceInterface
    bool addPropertyModel(oplink::QspObservablePropertyModel model) override;
    oplink::QspObservablePropertyModel getPropertyModel(oplink::PropertyModelName id) override;
    bool addProcessorModel(oplink::QspCommandProcessorModel model) override;
    oplink::QspCommandProcessorModel getProcessorModel(oplink::ProcessorModelName id) override;
    bool addObservableModel(oplink::QspObservableModel model) override;

protected: // ObservableBuilderServiceInterface
    oplink::QspObservableBuilder buildObservable(oplink::QspObservableBuilderArgs builderargs) override;

private:
    QspModelRegisterService     m_modelRegisterServiceImpl;
    QspObservableBuilderService m_observableBuilderServiceImpl;
};

#endif // OBSERVABLEMODELREGISTERPLUGIN_H
