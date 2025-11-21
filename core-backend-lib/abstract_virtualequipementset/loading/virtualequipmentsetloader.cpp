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
#include "virtualequipmentsetloaderargs.h"
#include "virtualequipmentsetconfreader.h"

oplink::VirtualEquipmentSetLoader::VirtualEquipmentSetLoader(oplink::VirtualEquipmentLoader *veLoader):
    m_veLoader{veLoader}
{

}

oplink::VirtualEquipmentSetLoader::~VirtualEquipmentSetLoader()
{

}

bool oplink::VirtualEquipmentSetLoader::startLoading()
{
    plugframe::QspWorkerArgs args{createWorkerArgs()};

    // start worker in a background thread
    startWork(args);

    return true;
}

plugframe::WorkerArgs *oplink::VirtualEquipmentSetLoader::createWorkerArgs()
{
    return new oplink::VirtualEquipmentSetLoaderArgs{m_veLoader};
}

plugframe::WorkerThread *oplink::VirtualEquipmentSetLoader::createWorkerThread(plugframe::QspWorkerArgs args)
{
    return new oplink::VirtualEquipmentSetConfReader{this, args};
}
