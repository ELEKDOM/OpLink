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


#ifndef INFRASTRUCTURECONTROLSERVICEINTERFACE_H
#define INFRASTRUCTURECONTROLSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "pfcore-lib_forward.h"

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

class InfrastructureControlServiceInterface : public plugframe::core::plugin::ServiceInterface
{        
public:
    static QString serviceName() {return QStringLiteral("InfrastructureControlServiceInterface");}

public:
        enum class OperationalMode {Operating, Setup};

public:
    virtual ~InfrastructureControlServiceInterface() {}

public:
    virtual const InfrastructureName& getInfrastructureName() = 0;

    // infrastructure loading is realized by a worker task. At the end of loading, the workerwatcher is notified
    virtual bool startLoadingInfrastructure(plugframe::core::worker::WorkerWatcher *workerWatcher,
                                            OperationalMode mode = OperationalMode::Operating) = 0;

    virtual bool loadingFinished() = 0;
};

}//namespace service
}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#define OlInfrastructureControlService_iid "elekdom.oplink.core.infrastructure.service.InfrastructureControlServiceInterface"
Q_DECLARE_INTERFACE(elekdom::oplink::core::infrastructure::service::InfrastructureControlServiceInterface, OlInfrastructureControlService_iid)

#endif // INFRASTRUCTURECONTROLSERVICEINTERFACE_H
