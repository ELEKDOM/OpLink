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

#include "virtualequipmentsetconfreader.h"
#include "virtualequipmentsetloaderargs.h"
#include "virtualequipmentsetloaderouts.h"
#include "virtualequipmentloader.h"
#include "abstract_virtualequipementset/virtualequipmentset.h"
#include "observable/observable/observable.h"

oplink::VirtualEquipmentSetConfReader::VirtualEquipmentSetConfReader(plugframe::WorkerSignal *wSignal,
                                                                     const plugframe::QspWorkerArgs& args):
    plugframe::WorkerThread{wSignal, args}
{

}

oplink::VirtualEquipmentSetConfReader::~VirtualEquipmentSetConfReader()
{

}

bool oplink::VirtualEquipmentSetConfReader::execWork(plugframe::QspWorkerArgs args)
{
    bool ret{true};
    oplink::QspVirtualEquipmentSetLoaderArgs wArgs{args.dynamicCast<oplink::VirtualEquipmentSetLoaderArgs>()};
    QStringList fileList;

    m_veSet = wArgs->m_veLoader->veSet();
    fileList = m_veSet->fileList();
    for (int i = 0; i < fileList.size() && ret; i++)
    {
        wArgs->m_veLoader->load(fileList.at(i));
        ret = !wArgs->m_veLoader->newly().isNull();
        if (ret)
        {
            m_veSet->getLoadedVirtualEquipments()->insert(wArgs->m_veLoader->newly()->name(),
                                                          wArgs->m_veLoader->newly());
        }
    }

    m_veSet->loadingFinished();

    return ret;
}

plugframe::WorkerOuts *oplink::VirtualEquipmentSetConfReader::getWorkerOuts()
{
    return new oplink::VirtualEquipmentSetLoaderOuts{m_veSet->getVirtualEquipmentSetName(),
                                                     m_ret,
                                                     m_veSet->getLoadedVirtualEquipments()};
}
