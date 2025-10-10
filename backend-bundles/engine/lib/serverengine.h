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


#ifndef SERVERENGINE_H
#define SERVERENGINE_H

#include <QHash>
#include <QList>
#include "bundle/bundleimplementation.h"
#include "olcore-backend-lib_forward.h"
#include "states/startinginfrastructuresstate.h"
#include "states/loadingvirtualequipmentsetsstate.h"
#include "states/startingclientsstate.h"

namespace elekdom
{
namespace oplink
{
namespace engine
{
namespace bundle
{

class ServerEngine: public plugframe::core::bundle::BundleImplementation
{  
public:
    ServerEngine();
    ~ServerEngine() override;

public:
    void startEngine();

public: // for states
    ConstIt_RegisteredInfras infrasBegin();
    ConstIt_RegisteredInfras infrasEnd();
    int nbInfras();
    ConstIt_RegisteredVirtualEquipmentSets virtualEquipmentSetsBegin();
    ConstIt_RegisteredVirtualEquipmentSets virtualEquipmentSetsEnd();
    int nbVirtualEquipmentSets();
    ConstIt_RegisteredFrontendItfs FrontendItfsBegin();
    ConstIt_RegisteredFrontendItfs FrontendItfsEnd();
    int nbFrontendItfs();
    void setLoadingVirtualEquipmentSetsState();
    void setStartingClientsState();
    void finished();
    void startCurrentState();
    void registerObservables(const observable::QspObservableBuildersContainer& loadedObservables);

#ifndef QT_NO_DEBUG_OUTPUT
    void printRegisteredInfrastructures();
#endif

protected:
    plugframe::core::bundle::BundleFactory* createFactory() override;
    void _start(plugframe::core::bundle::QspBundleContext bundleContext) override;
    plugframe::core::plugin::ServiceInterface *qtServiceInterface(const QString& sName) override;

private:
    List_RegisteredInfras               m_registeredInfrastructures;
    List_RegisteredVirtualEquipmentSet  m_registeredVirtualEquipmentSets;
    List_RegisteredFrontendItfs         m_registeredFrontendItfs;
    StartingInfrastructuresState        m_startingInfrastructuresState;
    LoadingVirtualEquipmentSetsState    m_loadingVirtualEquipmentSetsState;
    StartingClientsState                m_startingClientsState;
    ServerStartingState                *m_currentStartingState;
};

}//namespace bundle
}//namespace engine
}//namespace oplink
}//namespace elekdom

#endif // SERVERENGINE_H
