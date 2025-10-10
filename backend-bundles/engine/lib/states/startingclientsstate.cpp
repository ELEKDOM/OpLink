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


#include "startingclientsstate.h"
#include "worker/workerouts.h"
#include "logger/pflog.h"

using namespace elekdom::oplink::engine::bundle;

StartingClientsState::StartingClientsState(ServerEngine &engine):
    ServerStartingState{engine},
    m_nbFrontendItfs{0}
{

}

StartingClientsState::~StartingClientsState()
{

}

void StartingClientsState::starting()
{
    ConstIt_RegisteredFrontendItfs i;

    m_nbFrontendItfs = nbFrontendItfs();
    pfInfo1(logChannel()) << tr("%1 frontend interface(s) à charger ...").arg(m_nbFrontendItfs);

    if ( m_nbFrontendItfs > 0 )
    {
        for (i = FrontendItfsBegin();i != FrontendItfsEnd();i++)
        {
            (*i)->startListen();
        }
    }

    doTransition();
}

void StartingClientsState::doProcessing(const worker::QspWorkerOuts &outs)
{
    Q_UNUSED(outs)
}

bool StartingClientsState::test4transition()
{
    return true;
}

void StartingClientsState::transition()
{
    finished();
}
