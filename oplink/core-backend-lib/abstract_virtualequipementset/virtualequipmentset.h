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

#ifndef VIRTUALEQUIPMENTSET_H
#define VIRTUALEQUIPMENTSET_H

#include "bundle/bundleimplementation.h"
#include "abstract_virtualequipementset/loading/virtualequipmentsetloader.h"
#include "service-int/modelregisterserviceinterface.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "olcore-backend-lib_export.h"
#include "pfcore-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSet : public plugframe::BundleImplementation
{   
public:
    VirtualEquipmentSet(QString logBundleName);
    ~VirtualEquipmentSet() override;

public:
    void setVirtualEquipmentSetLoader(VirtualEquipmentSetLoader *virtualEquipmentSetLoader);
    const QString& getVirtualEquipmentSetName();
    QStringList fileList();
    void buildVirtualEquipment(QspHighObservableBuilderArgs builderArgs);
    QspObservableBuildersContainer getLoadedVirtualEquipments();
    void loadingFinished() {m_loadingFinished = true;}
    bool isLoadingFinished() {return m_loadingFinished;}
    bool startLoading(plugframe::WorkerWatcher *workerWatcher);

protected:
    ModelRegisterServiceInterface *modelRegisterService();
    plugframe::ServiceInterface *qtServiceInterface(const QString& sName) override;
    virtual void registerModels() = 0;

private:
    QspVirtualEquipmentSetLoader   m_virtualEquipmentSetLoader;
    QspObservableBuildersContainer m_loadedVirtualEquipments;
    bool                           m_loadingFinished;
};
}//namespace oplink
#endif // VIRTUALEQUIPMENTSET_H
