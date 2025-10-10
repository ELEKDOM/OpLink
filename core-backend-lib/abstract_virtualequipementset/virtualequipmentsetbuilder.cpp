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
#include "service/virtualequipmentsetservice.h"
#include "observable/virtualequipment/virtualequipmentconfdocument.h"
#include "observable/virtualequipment/virtualequipmentloaderhook.h"

using namespace elekdom::oplink::core::virtualequipmentset::builder;

VirtualEquipmentSetBuilder::VirtualEquipmentSetBuilder(plugframe::core::bundle::Bundle4BuilderInterface &myBundle):
    plugframe::core::bundle::BundleBuilder{myBundle}
{

}

VirtualEquipmentSetBuilder::~VirtualEquipmentSetBuilder()
{

}

void VirtualEquipmentSetBuilder::specificBuild()
{
    factory::VirtualEquipmentSetFactory&  veSetFactory{dynamic_cast<virtualequipmentset::factory::VirtualEquipmentSetFactory&>(getFactory())};
    bundle::VirtualEquipmentSet *veSet{dynamic_cast<virtualequipmentset::bundle::VirtualEquipmentSet*>(getImplementation())};
    virtualequipment::VirtualEquipmentLoader *equipmentLoader;
    virtualequipment::VirtualEquipmentConfDocument *confDocument;

    equipmentLoader = veSetFactory.createVirtualEquipmentLoader(veSet);
    veSet->setVirtualEquipmentSetLoader(veSetFactory.createVirtualEquipmentSetLoader(equipmentLoader));
    confDocument = veSetFactory.createVirtualEquipmentConfDocument(equipmentLoader->loaderHook());
    equipmentLoader->confDocument(confDocument);
}
