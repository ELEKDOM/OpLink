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

oplink::VirtualEquipmentSetConfReader::VirtualEquipmentSetConfReader(plugframe::WorkerSignal *wSignal,
                                                                     const plugframe::QspWorkerArgs& args):
    plugframe::WorkerThread{wSignal, args},
    m_veSet{nullptr}
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

    if (!wArgs.isNull() && !wArgs->m_veLoader.isNull() && wArgs->m_veLoader->veSet())
    {
        m_veSet = wArgs->m_veLoader->veSet();
        fileList = m_veSet->fileList();
        for (int i = 0; i < fileList.size() && ret; i++)
        {
            wArgs->m_veLoader->load(fileList.at(i));
            ret = !wArgs->m_veLoader->builderArgs().isNull();
            if (ret)
            {
                m_veSet->buildVirtualEquipment(wArgs->m_veLoader->builderArgs());
            }
        }
        m_veSet->loadingFinished();
    }
    else
    {
        ret = false;
    }

    return ret;
}

plugframe::WorkerOuts *oplink::VirtualEquipmentSetConfReader::getWorkerOuts()
{
    plugframe::WorkerOuts *ret{nullptr};

    if (m_veSet)
    {
        ret = new oplink::VirtualEquipmentSetLoaderOuts{m_veSet->getVirtualEquipmentSetName(),
                                                        m_ret,
                                                        m_veSet->getLoadedVirtualEquipments()};
    }

    return ret;
}
