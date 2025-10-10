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


#ifndef VIRTUALEQUIPMENTSETLOADER_H
#define VIRTUALEQUIPMENTSETLOADER_H

#include <QStringList>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "service-int/observableserviceinterface.h"
#include "worker/worker.h"

using namespace elekdom::plugframe::core;

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace virtualequipmentset
{

class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetLoader : public worker::Worker
{
public:
    VirtualEquipmentSetLoader(virtualequipment::VirtualEquipmentLoader *veLoader);
    ~VirtualEquipmentSetLoader() override;

public:
    bool startLoading();

protected:
    virtual worker::WorkerArgs *createWorkerArgs();
    worker::WorkerThread *createWorkerThread(worker::QspWorkerArgs args) override;

private:
    virtualequipment::QspVirtualEquipmentLoader m_veLoader;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // VIRTUALEQUIPMENTSETLOADER_H
