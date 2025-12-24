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

#include "loadingvirtualequipmentsetsstate.h"
#include "serverengine.h"
#include "logger/pflog.h"
#include "abstract_virtualequipementset/loading/virtualequipmentsetloaderouts.h"
#include "observable/observable/observablebuilder.h"

LoadingVirtualEquipmentSetsState::LoadingVirtualEquipmentSetsState(ServerEngine& engine):
    ServerStartingState{engine},
    m_nbVirtualEquipmentSets{0}
{

}

LoadingVirtualEquipmentSetsState::~LoadingVirtualEquipmentSetsState()
{

}

void LoadingVirtualEquipmentSetsState::starting()
{
    ConstIt_RegisteredVirtualEquipmentSets i;

    m_nbVirtualEquipmentSets = nbVirtualEquipmentSets();
    pfInfo1(logChannel()) << tr("%1 virtualequipment set(s) à charger ...").arg(m_nbVirtualEquipmentSets);

    if ( m_nbVirtualEquipmentSets > 0 )
    {
        for (i = virtualEquipmentSetsBegin();i != virtualEquipmentSetsEnd();i++)
        {
            if (!((*i)->startLoading(this)))
            {
                pfWarning2(logChannel()) << tr("Echec du lancement du chargement des équipments virtuels de type : ") << (*i)->getVirtualEquipmentSetName();
            }
        }
    }
    else
    {
        doTransition();
    }
}

void LoadingVirtualEquipmentSetsState::doProcessing(const plugframe::QspWorkerOuts &outs)
{
    plugframe::QspWorkerOuts qspouts(outs);
    oplink::QspVirtualEquipmentSetLoaderOuts loaderOuts(qspouts.dynamicCast<oplink::VirtualEquipmentSetLoaderOuts>());

    pfInfo1(logChannel()) << tr("Fin de chargement pour ") << loaderOuts->m_virtualEquipmentSetName << ", loadedFlag = " << loaderOuts->m_ret;

    if (loaderOuts->m_ret)
    {
        // Start all scheduler if needed !
        initScheduler(loaderOuts->m_loadedVirtualEquipments);

        // Register all virtual equipmeents
        registerObservables(loaderOuts->m_loadedVirtualEquipments);
    }
}

bool LoadingVirtualEquipmentSetsState::test4transition()
{
    pfDebug3(logChannel()) << "->GacLoadingVirtualEquipmentSetsState::test4transition";
    bool ret{true};
    ConstIt_RegisteredVirtualEquipmentSets i;

    for (i = virtualEquipmentSetsBegin();i != virtualEquipmentSetsEnd() && ret;i++)
    {
        ret = (*i)->loadingFinished();
        pfDebug4(logChannel()) << (*i)->getVirtualEquipmentSetName() << ", loaded=" << ret;
    }

    pfDebug3(logChannel()) << "<-GacLoadingVirtualEquipmentSetsState::test4transition, ret=" << ret;

    return ret;
}

void LoadingVirtualEquipmentSetsState::transition()
{
    setStartingClientsState();
}

void LoadingVirtualEquipmentSetsState::initScheduler(oplink::QspObservableBuildersContainer loadedVirtualEquipments)
{
    for(oplink::ObservableBuildersContainer::ConstIt it = loadedVirtualEquipments->begin(); it != loadedVirtualEquipments->end(); it++)
    {
        oplink::QspObservableBuilder ve{*it};

        ve->initScheduler();
    }
}
