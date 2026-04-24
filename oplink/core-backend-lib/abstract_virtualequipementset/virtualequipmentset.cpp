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

#include <QDir>
#include "virtualequipmentset.h"
#include "worker/workerwatcher.h"
#include "bundle/bundlecontext.h"
#include "service-int/virtualequipmentsetserviceinterface.h"
#include "service-int/observablebuilderserviceinterface.h"
#include "service-int/observableserviceinterface.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "abstract_virtualequipementset/loading/virtualequipmentsetloader.h"

oplink::VirtualEquipmentSet::VirtualEquipmentSet(QString logBundleName):
    plugframe::BundleImplementation{logBundleName},
    m_loadedVirtualEquipments{new oplink::ObservableBuildersContainer},
    m_loadingFinished{false}
{

}

oplink::VirtualEquipmentSet::~VirtualEquipmentSet()
{

}

void oplink::VirtualEquipmentSet::setVirtualEquipmentSetLoader(oplink::VirtualEquipmentSetLoader *virtualEquipmentSetLoader)
{
    m_virtualEquipmentSetLoader.reset(virtualEquipmentSetLoader);
}

const QString& oplink::VirtualEquipmentSet::getVirtualEquipmentSetName()
{
    return getLogBundleName();
}

QStringList oplink::VirtualEquipmentSet::fileList()
{
    QStringList namesFilter{"*.xml"};
    QStringList filenames;
    QStringList ret;
    QString path{getConfDir()};
    QDir confDir{path};

    filenames = confDir.entryList(namesFilter, QDir::Files);
    for (int i = 0; i < filenames.size(); ++i)
    {
        ret << path + filenames[i];
    }

    return ret;
}

void oplink::VirtualEquipmentSet::buildVirtualEquipment(QspHighObservableBuilderArgs builderArgs)
{
    // Once the heating manager description XML file has been loaded, the Observables construction service
    // must be invoked to create the HeatingManager.
    oplink::ObservableBuilderServiceInterface *builderService{bundleContext()->getService<ObservableBuilderServiceInterface>(ObservableBuilderServiceInterface::serviceName())};
    oplink::QspObservableBuilder newHeatingManager;

    builderArgs->m_observableService = bundleContext()->getService<ObservableServiceInterface>(oplink::ObservableServiceInterface::serviceName());

    if (builderService && builderArgs->m_observableService)
    {
        newHeatingManager = builderService->buildObservable(builderArgs);
    }

    // Store the new Observable to transmit it at the end of the loading process.
    if (!newHeatingManager.isNull())
    {
        m_loadedVirtualEquipments->insert(builderArgs->m_observableName,newHeatingManager);
    }
}

oplink::QspObservableBuildersContainer oplink::VirtualEquipmentSet::getLoadedVirtualEquipments()
{
    return m_loadedVirtualEquipments;
}

///
/// \brief oplink::VirtualEquipmentSet::startLoading
/// launches a background task to load all the XML files describing the virtual equipment to be loaded.
/// \param workerWatcher, the item to report at the end of the task
/// \return true if the task is launched
///
bool oplink::VirtualEquipmentSet::startLoading(plugframe::WorkerWatcher *workerWatcher)
{
    bool ret{false};

    // First register models for building the specific HighObservable (VirtualEquipment)
    registerModels();

    // Set Connection for work finished signal
    workerWatcher->connectWorker(m_virtualEquipmentSetLoader.get());

    // Load all ve in background
    ret = m_virtualEquipmentSetLoader->startLoading();
    return ret;
}

oplink::ModelRegisterServiceInterface *oplink::VirtualEquipmentSet::modelRegisterService()
{
    return bundleContext()->getService<oplink::ModelRegisterServiceInterface>(oplink::ModelRegisterServiceInterface::serviceName());
}

plugframe::ServiceInterface *oplink::VirtualEquipmentSet::qtServiceInterface(const QString &sName)
{
    plugframe::ServiceInterface *ret{nullptr};

    if (oplink::VirtualEquipmentSetServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<oplink::VirtualEquipmentSetServiceInterface*>(getQplugin());
    }

    return ret;
}
