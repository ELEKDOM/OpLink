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
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "service-int/observableserviceinterface.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipmentset
{
namespace bundle
{

class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSet : public plugframe::core::bundle::BundleImplementation
{
public:
    VirtualEquipmentSet(QString logBundleName);
    ~VirtualEquipmentSet()  override;

public:
    void setVirtualEquipmentSetLoader(VirtualEquipmentSetLoader *virtualEquipmentSetLoader);
    const QString& getVirtualEquipmentSetName();
    QStringList fileList();
    observable::QspObservableBuildersContainer getLoadedVirtualEquipments();
    void loadingFinished() {m_loadingFinished = true;}
    bool isLoadingFinished() {return m_loadingFinished;}
    engine::service::ObservableServiceInterface* observableService();
    bool startLoading(plugframe::core::worker::WorkerWatcher *workerWatcher);

protected:
    plugframe::core::plugin::ServiceInterface *qtServiceInterface(const QString& sName) override;

private:
    QspVirtualEquipmentSetLoader               m_virtualEquipmentSetLoader;
    observable::QspObservableBuildersContainer m_loadedVirtualEquipments;
    bool                                       m_loadingFinished;
};

}//namespace bundle
}//namespace virtualequipmentset
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTSET_H
