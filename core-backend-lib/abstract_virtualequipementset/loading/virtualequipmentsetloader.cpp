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


#include "virtualequipmentsetloader.h"
#include "virtualequipmentloader.h"
#include "virtualequipmentsetloaderargs.h"
#include "virtualequipmentsetconfreader.h"

using namespace elekdom::oplink::core::virtualequipmentset;

VirtualEquipmentSetLoader::VirtualEquipmentSetLoader(virtualequipment::VirtualEquipmentLoader *veLoader):
    m_veLoader{veLoader}
{

}

VirtualEquipmentSetLoader::~VirtualEquipmentSetLoader()
{

}

bool VirtualEquipmentSetLoader::startLoading()
{
    worker::QspWorkerArgs args{createWorkerArgs()};

    // start worker in a background thread
    startWork(args);

    return true;
}

worker::WorkerArgs *VirtualEquipmentSetLoader::createWorkerArgs()
{
    return new VirtualEquipmentSetLoaderArgs{m_veLoader};
}

worker::WorkerThread *VirtualEquipmentSetLoader::createWorkerThread(worker::QspWorkerArgs args)
{
    return new VirtualEquipmentSetConfReader{this, args};
}
