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

using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class EnoceanInfrastructureLoader : public infrastructure::InfrastructureLoader
{
public:
    EnoceanInfrastructureLoader(const QString& logChannel,
                                infrastructure::InfrastructureLoadingOperations& infrastructure);
    ~EnoceanInfrastructureLoader() override;

protected:
    worker::WorkerThread *createWorkerThread(worker::QspWorkerArgs args) override;
    infrastructure::DeviceBuilder *createDeviceBuilder(const infrastructure::QspDeviceProcessorBuilder& processorBuilder) override;
    infrastructure::AreaGateway *createGateway(infrastructure::GatewayArgs& gatewayArgs) override;
    virtual EnoceanGateway *createGateway(EnoceanGatewayMode *mode);
    virtual EnoceanGatewayMode *createGatewayMode() = 0;
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ENOCEANINFRASTRUCTURELOADER_H
