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

oplink::QspObservableBuildersContainer oplink::VirtualEquipmentSet::getLoadedVirtualEquipments()
{
    return m_loadedVirtualEquipments;
}

oplink::ObservableServiceInterface *oplink::VirtualEquipmentSet::observableService()
{
    oplink::ObservableServiceInterface *obsService;
    obsService = bundleContext()->getService<oplink::ObservableServiceInterface>(oplink::ObservableServiceInterface::serviceName());
    return obsService;
}

bool oplink::VirtualEquipmentSet::startLoading(plugframe::WorkerWatcher *workerWatcher)
{
    bool ret{false};

    // Set Connection for work finished signal
    workerWatcher->connectWorker(m_virtualEquipmentSetLoader.get());

    // Load all ve in background
    ret = m_virtualEquipmentSetLoader->startLoading();
    return ret;
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
