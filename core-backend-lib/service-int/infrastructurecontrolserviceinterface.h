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
#include "worker/workerwatcher.h"

namespace oplink
{
class InfrastructureControlServiceInterface : public plugframe::ServiceInterface
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
    virtual bool startLoadingInfrastructure(plugframe::WorkerWatcher *workerWatcher,
                                            OperationalMode mode = OperationalMode::Operating) = 0;

    virtual bool loadingFinished() = 0;
};
}//namespace oplink

#define OlInfrastructureControlService_iid "oplink.InfrastructureControlServiceInterface"
Q_DECLARE_INTERFACE(oplink::InfrastructureControlServiceInterface, OlInfrastructureControlService_iid)

#endif // INFRASTRUCTURECONTROLSERVICEINTERFACE_H
