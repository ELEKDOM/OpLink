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
#include "virtualequipmentsetfactory.h"
#include "worker/workerwatcher.h"
#include "bundle/bundlecontext.h"
#include "service-int/virtualequipmentsetserviceinterface.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "abstract_virtualequipementset/loading/virtualequipmentsetloader.h"
#include "abstract_virtualequipementset/loading/virtualequipmentloader.h"

using namespace elekdom::oplink;
using namespace elekdom::oplink::core::virtualequipmentset::bundle;
using namespace elekdom::oplink::core::virtualequipmentset;

VirtualEquipmentSet::VirtualEquipmentSet(QString logBundleName):
    plugframe::core::bundle::BundleImplementation{logBundleName},
    m_loadedVirtualEquipments{new observable::ObservableBuildersContainer},
    m_loadingFinished{false}
{

}

VirtualEquipmentSet::~VirtualEquipmentSet()
{

}

void VirtualEquipmentSet::setVirtualEquipmentSetLoader(VirtualEquipmentSetLoader *virtualEquipmentSetLoader)
{
    m_virtualEquipmentSetLoader.reset(virtualEquipmentSetLoader);
}

const QString& VirtualEquipmentSet::getVirtualEquipmentSetName()
{
    return getLogBundleName();
}

QStringList VirtualEquipmentSet::fileList()
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

core::observable::QspObservableBuildersContainer VirtualEquipmentSet::getLoadedVirtualEquipments()
{
    return m_loadedVirtualEquipments;
}

engine::service::ObservableServiceInterface *VirtualEquipmentSet::observableService()
{
    engine::service::ObservableServiceInterface *obsService;
    obsService = bundleContext()->getService<engine::service::ObservableServiceInterface>(engine::service::ObservableServiceInterface::serviceName());
    return obsService;
}

bool VirtualEquipmentSet::startLoading(plugframe::core::worker::WorkerWatcher *workerWatcher)
{
    bool ret{false};

    // Set Connection for work finished signal
    workerWatcher->connectWorker(m_virtualEquipmentSetLoader.get());

    // Load all ve in background
    ret = m_virtualEquipmentSetLoader->startLoading();
    return ret;
}

plugin::ServiceInterface *VirtualEquipmentSet::qtServiceInterface(const QString &sName)
{
    plugframe::core::plugin::ServiceInterface *ret{nullptr};

    if (service::VirtualEquipmentSetServiceInterface::serviceName() == sName)
    {
        ret = qobject_cast<service::VirtualEquipmentSetServiceInterface*>(getQplugin());
    }

    return ret;
}
