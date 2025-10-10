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


#ifndef SERVERSTARTINGSTATE_H
#define SERVERSTARTINGSTATE_H

#include "worker/workerwatcher.h"
#include "service-int/backendcontrolserviceinterface.h"
#include "service-int/infrastructurecontrolserviceinterface.h"
#include "service-int/virtualequipmentsetserviceinterface.h"
#include "olcore-backend-lib_forward.h"
#include "serverengine_forward.h"

using namespace elekdom::plugframe::core;
using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace engine
{
namespace bundle
{

using List_RegisteredInfras = QList<infrastructure::service::InfrastructureControlServiceInterface*>;
using ConstIt_RegisteredInfras = List_RegisteredInfras::const_iterator;

using List_RegisteredVirtualEquipmentSet = QList<virtualequipmentset::service::VirtualEquipmentSetServiceInterface*>;
using ConstIt_RegisteredVirtualEquipmentSets =  List_RegisteredVirtualEquipmentSet::const_iterator;

using List_RegisteredFrontendItfs = QList<plugframe::frontenditf::service::BackendControlServiceInterface*>;
using ConstIt_RegisteredFrontendItfs = List_RegisteredFrontendItfs::const_iterator;

class ServerStartingState : public worker::WorkerWatcher
{
public:
    ServerStartingState(ServerEngine& engine);
    ~ServerStartingState() override;

public:
    virtual void starting() = 0;

protected:
    void onWorkFinished(worker::QspWorkerOuts outs) override;
    virtual void doProcessing(const worker::QspWorkerOuts& outs) = 0;
    virtual bool test4transition() = 0;
    virtual void transition() = 0;

protected:
    const QString &logChannel();
    ConstIt_RegisteredInfras infrasBegin();
    ConstIt_RegisteredInfras infrasEnd();
    int nbInfras();
    ConstIt_RegisteredVirtualEquipmentSets virtualEquipmentSetsBegin();
    ConstIt_RegisteredVirtualEquipmentSets virtualEquipmentSetsEnd();
    int nbVirtualEquipmentSets();
    ConstIt_RegisteredFrontendItfs FrontendItfsBegin();
    ConstIt_RegisteredFrontendItfs FrontendItfsEnd();
    int nbFrontendItfs();
    void registerObservables(const observable::QspObservableBuildersContainer& loadedObservables);
    void setLoadingVirtualEquipmentSetsState();
    void setStartingClientsState();
    void finished();

protected:
    void doTransition();

protected:
    ServerEngine& m_engine;
};

}//namespace bundle
}//namespace engine
}//namespace oplink
}//namespace elekdom

#endif // SERVERSTARTINGSTATE_H
