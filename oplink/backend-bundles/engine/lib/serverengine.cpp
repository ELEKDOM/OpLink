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

#include <QMutexLocker>
#include "logger/pflog.h"
#include "bundle/bundlecontext.h"
#include "serverengine.h"
#include "serverenginefactory.h"
#include "serverengine_forward.h"
#include "observableservice.h"
#include "service-int/systemserviceinterface.h"
#include "service-int/observableserviceinterface.h"
#include "observable/observable/observablebuilderscontainer.h"

ServerEngine::ServerEngine():
   plugframe::BundleImplementation{"ServerEngine"},
   m_startingInfrastructuresState{*this},
   m_loadingVirtualEquipmentSetsState{*this},
   m_startingClientsState{*this},
   m_currentStartingState{&m_startingInfrastructuresState}
{
    qRegisterMetaType<oplink::ObservableName>("oplink::ObservableName");
    qRegisterMetaType<oplink::PropertyName>("oplink::PropertyName");
}

ServerEngine::~ServerEngine()
{

}

void ServerEngine::startEngine()
{
    pfDebug3(logChannel()) << "->GacServerEngine::startEngine";

    // Retrieves the registered infrastructures
    m_registeredInfrastructures = bundleContext()->getServices<oplink::InfrastructureControlServiceInterface>(oplink::InfrastructureControlServiceInterface::serviceName());

#ifndef QT_NO_DEBUG_OUTPUT
    printRegisteredInfrastructures();
#endif

    // Retrieves the registered virtualequipment sets
    m_registeredVirtualEquipmentSets = bundleContext()->getServices<oplink::VirtualEquipmentSetServiceInterface>(oplink::VirtualEquipmentSetServiceInterface::serviceName());

    // Retrieves the registered frontenditfs
    m_registeredFrontendItfs = bundleContext()->getServices<plugframe::BackendControlServiceInterface>(plugframe::BackendControlServiceInterface::serviceName());

    // Starts background loading !
    m_currentStartingState = &m_startingInfrastructuresState;
    m_currentStartingState->starting();

    pfDebug3(logChannel()) << "<-GacServerEngine::startEngine";
}

ConstIt_RegisteredInfras ServerEngine::infrasBegin()
{
    return m_registeredInfrastructures.constBegin();
}

ConstIt_RegisteredInfras ServerEngine::infrasEnd()
{
    return m_registeredInfrastructures.constEnd();
}

int ServerEngine::nbInfras()
{
    return m_registeredInfrastructures.size();
}

ConstIt_RegisteredVirtualEquipmentSets ServerEngine::virtualEquipmentSetsBegin()
{
     return m_registeredVirtualEquipmentSets.constBegin();
}

ConstIt_RegisteredVirtualEquipmentSets ServerEngine::virtualEquipmentSetsEnd()
{
    return m_registeredVirtualEquipmentSets.constEnd();
}

int ServerEngine::nbVirtualEquipmentSets()
{
    return m_registeredVirtualEquipmentSets.size();
}

ConstIt_RegisteredFrontendItfs ServerEngine::FrontendItfsBegin()
{
    return m_registeredFrontendItfs.constBegin();
}

ConstIt_RegisteredFrontendItfs ServerEngine::FrontendItfsEnd()
{
    return m_registeredFrontendItfs.constEnd();
}

int ServerEngine::nbFrontendItfs()
{
    return m_registeredFrontendItfs.size();
}

void ServerEngine::setLoadingVirtualEquipmentSetsState()
{
    m_currentStartingState = &m_loadingVirtualEquipmentSetsState;
}

void ServerEngine::setStartingClientsState()
{
    m_currentStartingState = &m_startingClientsState;
}

void ServerEngine::finished()
{
    m_currentStartingState = nullptr;
}

void ServerEngine::startCurrentState()
{
    if (m_currentStartingState != nullptr)
    {
        m_currentStartingState->starting();
    }
}

void ServerEngine::registerObservables(const oplink::QspObservableBuildersContainer &loadedObservables)
{
    plugframe::QspServiceImplementationInterface serviceImplementationItf;
    QspObservableService                         observableServiceImpl;

    serviceImplementationItf = getServiceImplementation(oplink::ObservableServiceInterface::serviceName());
    observableServiceImpl = serviceImplementationItf.dynamicCast<ObservableService>();

    if (observableServiceImpl)
    {
        observableServiceImpl->registerObservables(loadedObservables);
    }
}

#ifndef QT_NO_DEBUG_OUTPUT
void ServerEngine::printRegisteredInfrastructures()
{
    for (int i = 0; i < m_registeredInfrastructures.size(); ++i) {
        pfDebug4(logChannel()) << "Registered Infrastructure [" << i << "] is " << (m_registeredInfrastructures.at(i))->getInfrastructureName();
    }
}
#endif

plugframe::BundleFactory *ServerEngine::createFactory()
{
    return new ServerEngineFactory;
}

void ServerEngine::_start(plugframe::QspBundleContext bundleContext)
{
    plugframe::BundleImplementation::_start(bundleContext);

    plugframe::SystemServiceInterface *systemServiceItf;
    systemServiceItf = bundleContext->getService<plugframe::SystemServiceInterface>(plugframe::SystemServiceInterface::serviceName());

    // Register the listener to wait for framework started evt
    systemServiceItf->registerListener(getListener().get());
}

plugframe::ServiceInterface *ServerEngine::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (oplink::ObservableServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<oplink::ObservableServiceInterface*>(getQplugin());
    }

    return ret;
}
