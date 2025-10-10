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


#include <QCoreApplication>
#include "worker/workerargs.h"
#include "abstract_infrastructure/loading/deviceprocessorbuilder.h"
#include "loader/enoceaninfrastructureloader.h"
#include "loader/enoceanconfreader.h"
#include "loader/enoceandevicebuilder.h"
#include "loader/enoceangatewayargs.h"
#include "gateway/enoceangateway.h"

using namespace elekdom::oplink::enocean;

EnoceanInfrastructureLoader::EnoceanInfrastructureLoader(const QString& logChannel,
                                                         infrastructure::InfrastructureLoadingOperations& infrastructure):
    infrastructure::InfrastructureLoader{logChannel, infrastructure}
{

}

EnoceanInfrastructureLoader::~EnoceanInfrastructureLoader()
{

}

worker::WorkerThread *EnoceanInfrastructureLoader::createWorkerThread(worker::QspWorkerArgs args)
{
    return new EnoceanConfReader(logChannel(),
                                 *this,
                                 this,
                                 args);
}

infrastructure::DeviceBuilder *EnoceanInfrastructureLoader::createDeviceBuilder(const infrastructure::QspDeviceProcessorBuilder &processorBuilder)
{
    return new EnoceanDeviceBuilder(processorBuilder);
}

infrastructure::AreaGateway *EnoceanInfrastructureLoader::createGateway(infrastructure::GatewayArgs& gatewayArgs)
{
   EnoceanGateway *gateway;
   EnoceanGatewayArgs& enoceanGatewayArgs{dynamic_cast<EnoceanGatewayArgs&>(gatewayArgs)};
   EnoceanGatewayMode *gatewayMode{createGatewayMode()};

   gateway = createGateway(gatewayMode);
   enoceanGatewayArgs.accept(*gateway);
   gateway->moveToThread(QCoreApplication::instance()->thread());

   return gateway;
}

EnoceanGateway *EnoceanInfrastructureLoader::createGateway(EnoceanGatewayMode *mode)
{
    return new EnoceanGateway(logChannel(), mode);
}
