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

#ifndef VIRTUALEQUIPMENTSETCONFREADER_H
#define VIRTUALEQUIPMENTSETCONFREADER_H

#include "worker/workerthread.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT VirtualEquipmentSetConfReader : public plugframe::WorkerThread
{
public:
    VirtualEquipmentSetConfReader(plugframe::WorkerSignal *wSignal,
                                  const plugframe::QspWorkerArgs& args);
    ~VirtualEquipmentSetConfReader() override;

protected: // SmfWorkerThread
    bool execWork(plugframe::QspWorkerArgs args) override;
    plugframe::WorkerOuts *getWorkerOuts() override;

private:
    VirtualEquipmentSet *m_veSet;
};
}//namespace oplink
#endif // VIRTUALEQUIPMENTSETCONFREADER_H
