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

#ifndef ENOCEANINFRASTRUCTURELOADER_H
#define ENOCEANINFRASTRUCTURELOADER_H

#include "abstract_infrastructure/loading/infrastructureloader.h"
#include "enoceaninfrastructure_forward.h"

class EnoceanInfrastructureLoader : public oplink::InfrastructureLoader
{
public:
    EnoceanInfrastructureLoader(const QString& logChannel,
                                oplink::InfrastructureLoadingOperations& infrastructure);
    ~EnoceanInfrastructureLoader() override;

protected:
    plugframe::WorkerThread *createWorkerThread(plugframe::QspWorkerArgs args) override;
    oplink::DeviceBuilder *createDeviceBuilder(const oplink::QspDeviceProcessorBuilder& processorBuilder) override;
    oplink::AreaGateway *createGateway(oplink::GatewayArgs& gatewayArgs) override;
    virtual EnoceanGateway *createGateway(EnoceanGatewayMode *mode);
    virtual EnoceanGatewayMode *createGatewayMode() = 0;
};
#endif // ENOCEANINFRASTRUCTURELOADER_H
