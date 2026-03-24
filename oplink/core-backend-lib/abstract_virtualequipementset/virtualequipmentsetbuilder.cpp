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

#include "virtualequipmentsetbuilder.h"
#include "virtualequipmentsetfactory.h"
#include "virtualequipmentset.h"
#include "abstract_virtualequipementset/loading/virtualequipmentloader.h"
#include "observable/highobservable/highobservableconfdocument.h"

oplink::VirtualEquipmentSetBuilder::VirtualEquipmentSetBuilder(plugframe::Bundle4BuilderInterface &myBundle):
    plugframe::BundleBuilder{myBundle}
{

}

oplink::VirtualEquipmentSetBuilder::~VirtualEquipmentSetBuilder()
{

}

void oplink::VirtualEquipmentSetBuilder::specificBuild()
{
    oplink::VirtualEquipmentSetFactory&  veSetFactory{dynamic_cast<oplink::VirtualEquipmentSetFactory&>(getFactory())};
    oplink::VirtualEquipmentSet *veSet{dynamic_cast<oplink::VirtualEquipmentSet*>(getImplementation())};
    oplink::VirtualEquipmentLoader *equipmentLoader;
    oplink::HighObservableConfDocument *confDocument;

    equipmentLoader = veSetFactory.createVirtualEquipmentLoader(veSet);
    veSet->setVirtualEquipmentSetLoader(veSetFactory.createVirtualEquipmentSetLoader(equipmentLoader));
    confDocument = veSetFactory.createVirtualEquipmentConfDocument(equipmentLoader->loaderHook());
    equipmentLoader->confDocument(confDocument);
}
