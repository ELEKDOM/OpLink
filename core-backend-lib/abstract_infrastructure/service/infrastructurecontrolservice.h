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


#ifndef INFRASTRUCTURECONTROLSERVICE_H
#define INFRASTRUCTURECONTROLSERVICE_H

#include "olcore-backend-lib_export.h"
#include "service/serviceimplementation.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "service-int/infrastructurecontrolserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{
namespace service
{

class OLCORE_BACKEND_LIB_EXPORT InfrastructureControlService : public plugframe::core::service::ServiceImplementation
{
public:
    InfrastructureControlService(plugframe::core::bundle::BundleImplementation *implementation);
    ~InfrastructureControlService() override;

public:
    const InfrastructureName& getInfrastructureName();
    bool startLoadingInfrastructure(plugframe::core::worker::WorkerWatcher *workerWatcher,
                                    InfrastructureControlServiceInterface::OperationalMode mode = InfrastructureControlServiceInterface::OperationalMode::Operating);
    bool loadingFinished();

protected:
    QString serviceName() override;
};

}//namespace service
}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // INFRASTRUCTURECONTROLSERVICE_H
