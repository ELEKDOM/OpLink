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

#ifndef INFRASTRUCTUREPLUGIN_H
#define INFRASTRUCTUREPLUGIN_H

#include "plugin/plugin.h"
#include "service-int/infrastructurecontrolserviceinterface.h"
#include "abstract_infrastructure/service/infrastructurecontrolservice.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT InfrastructurePlugin : public plugframe::Plugin,
                                                       public InfrastructureControlServiceInterface
{
public:
    InfrastructurePlugin();
    ~InfrastructurePlugin() override;

protected: // Plugin
    void bindServicesImplementations() override;

protected: // InfrastructureControlServiceInterface
    const InfrastructureName& getInfrastructureName() override;
    bool startLoadingInfrastructure(plugframe::WorkerWatcher *workerWatcher,
                                    OperationalMode mode = OperationalMode::Operating) override;
    bool loadingFinished() override;

private:
    QspInfrastructureControlService m_controlServiceImpl;
};
}//namespace oplink
#endif // INFRASTRUCTUREPLUGIN_H
