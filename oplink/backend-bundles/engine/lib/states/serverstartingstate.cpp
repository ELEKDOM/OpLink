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

#include "serverstartingstate.h"
#include "worker/workerouts.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "serverengine.h"

ServerStartingState::ServerStartingState(ServerEngine& engine):
    m_engine{engine}
{

}

ServerStartingState::~ServerStartingState()
{

}

void ServerStartingState::onWorkFinished(plugframe::QspWorkerOuts outs)
{
    doProcessing(outs);
    if (test4transition())
    {
        doTransition();
    }
}

const QString &ServerStartingState::logChannel()
{
    return m_engine.logChannel();
}

ConstIt_RegisteredInfras ServerStartingState::infrasBegin()
{
    return m_engine.infrasBegin();
}

ConstIt_RegisteredInfras ServerStartingState::infrasEnd()
{
    return m_engine.infrasEnd();
}

int ServerStartingState::nbInfras()
{
    return m_engine.nbInfras();
}

ConstIt_RegisteredVirtualEquipmentSets ServerStartingState::virtualEquipmentSetsBegin()
{
    return m_engine.virtualEquipmentSetsBegin();
}

ConstIt_RegisteredVirtualEquipmentSets ServerStartingState::virtualEquipmentSetsEnd()
{
    return m_engine.virtualEquipmentSetsEnd();
}

int ServerStartingState::nbVirtualEquipmentSets()
{
    return m_engine.nbVirtualEquipmentSets();
}

ConstIt_RegisteredFrontendItfs ServerStartingState::FrontendItfsBegin()
{
    return m_engine.FrontendItfsBegin();
}

ConstIt_RegisteredFrontendItfs ServerStartingState::FrontendItfsEnd()
{
    return m_engine.FrontendItfsEnd();
}

int ServerStartingState::nbFrontendItfs()
{
    return m_engine.nbFrontendItfs();
}

void ServerStartingState::registerObservables(const oplink::QspObservableBuildersContainer &loadedObservables)
{
    m_engine.registerObservables(loadedObservables);
}

void ServerStartingState::setLoadingVirtualEquipmentSetsState()
{
    m_engine.setLoadingVirtualEquipmentSetsState();
}

void ServerStartingState::setStartingClientsState()
{
    m_engine.setStartingClientsState();
}

void ServerStartingState::finished()
{
    m_engine.finished();
}

oplink::ObservableServiceInterface *ServerStartingState::observableServiceIt()
{
    return m_engine.observableServiceIt();
}

void ServerStartingState::doTransition()
{
    transition();
    m_engine.startCurrentState();
}
