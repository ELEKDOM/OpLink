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

#include "startinginfrastructuresstate.h"
#include "serverengine.h"
#include "logger/pflog.h"
#include "worker/workerouts.h"
#include "abstract_infrastructure/loading/infrastructureloaderouts.h"

StartingInfrastructuresState::StartingInfrastructuresState(ServerEngine& engine):
    ServerStartingState{engine},
    m_nbInfras{0}
{

}

StartingInfrastructuresState::~StartingInfrastructuresState()
{

}

void StartingInfrastructuresState::starting()
{
    ConstIt_RegisteredInfras i;

    m_nbInfras = nbInfras();
    pfInfo1(logChannel()) << tr("%1 infrastructure(s) à charger ...").arg(m_nbInfras);

    if ( m_nbInfras > 0 )
    {
        for (i = infrasBegin();i != infrasEnd();i++)
        {
            if (!((*i)->startLoadingInfrastructure(this)))
            {
                pfWarning2(logChannel()) << tr("Echec du lancement du chargement de l'infrastructure : ") << (*i)->getInfrastructureName();
            }
        }
    }
    else
    {
        doTransition();
    }
}

void StartingInfrastructuresState::doProcessing(const plugframe::QspWorkerOuts &outs)
{
    plugframe::QspWorkerOuts qspouts(outs);
    oplink::QspInfrastructureLoaderOuts loaderOuts(qspouts.dynamicCast<oplink::InfrastructureLoaderOuts>());

    pfInfo1(logChannel()) << tr("Fin de chargement pour ") << loaderOuts->m_infrastructureName << ", loadedFlag = " << loaderOuts->m_ret;

    if (loaderOuts->m_ret)
    {
        registerObservables(loaderOuts->m_loadedObservables);
    }
}

bool StartingInfrastructuresState::test4transition()
{
    pfDebug3(logChannel()) << "->GacStartingInfrastructuresState::test4transition";
    bool ret{true};
    ConstIt_RegisteredInfras i;

    for (i = infrasBegin();i != infrasEnd() && ret;i++)
    {
        ret = (*i)->loadingFinished();
        pfDebug4(logChannel()) << (*i)->getInfrastructureName() << ", loaded=" << ret;
    }

    pfDebug3(logChannel()) << "<-GacStartingInfrastructuresState::test4transition, ret=" << ret;

    return ret;
}

void StartingInfrastructuresState::transition()
{
    setLoadingVirtualEquipmentSetsState();
}
