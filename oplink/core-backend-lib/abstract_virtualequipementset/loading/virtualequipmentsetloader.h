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
#include <QSharedPointer>
#include "virtualequipmentloader.h"
#include "worker/worker.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
/**
 * @brief The VirtualEquipmentSetLoader class
 * Generic loader for virtual devices (derived from HighObservable)
 * A virtual device is defined in an XML file.
 * The device is always built using a specific model.
 */
class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetLoader : public plugframe::Worker
{
public:
    VirtualEquipmentSetLoader(VirtualEquipmentLoader *veLoader);
    ~VirtualEquipmentSetLoader() override;

public:
    bool startLoading();

protected:
    virtual plugframe::WorkerArgs *createWorkerArgs();
    plugframe::WorkerThread *createWorkerThread(plugframe::QspWorkerArgs args) override;

private:
    QspVirtualEquipmentLoader m_veLoader;
};
using QspVirtualEquipmentSetLoader = QSharedPointer<VirtualEquipmentSetLoader>;
}//namespace oplink
#endif // VIRTUALEQUIPMENTSETLOADER_H
