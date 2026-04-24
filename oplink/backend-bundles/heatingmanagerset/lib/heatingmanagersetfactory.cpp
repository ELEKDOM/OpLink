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

#include "heatingmanagersetfactory.h"
#include "heatingmanager/heatingmanagerloader.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanagerconfdocument.h"
#include "observable/heatingmanagermodelnames.h"
#include "model/observable/highobservable/supervisorobservable/heatingmanager/heatingmanagerpwmodel.h"
#include "model/observable/highobservable/supervisorobservable/heatingmanager/heatingmanagerpwtmodel.h"

HeatingManagerSetFactory::HeatingManagerSetFactory()
{

}

HeatingManagerSetFactory::~HeatingManagerSetFactory()
{

}

oplink::ObservableModel *HeatingManagerSetFactory::createHeatingManagerPwModel()
{
    return new oplink::HeatingManagerPwModel{oplink::HeatingManagerModelNames::pilotWireModelName()};
}

oplink::ObservableModel *HeatingManagerSetFactory::createHeatingManagerPwtModel()
{
    return new oplink::HeatingManagerPwtModel{oplink::HeatingManagerModelNames::pilotWireThermostatModelName()};
}

oplink::VirtualEquipmentLoader *HeatingManagerSetFactory::createVirtualEquipmentLoader(oplink::VirtualEquipmentSet *veSet)
{
    return new HeatingManagerLoader{veSet};
}

oplink::HighObservableConfDocument *HeatingManagerSetFactory::createVirtualEquipmentConfDocument(oplink::HighObservableLoaderHook &hook)
{
    oplink::HeatingManagerLoaderHook& loaderHook{dynamic_cast<oplink::HeatingManagerLoaderHook&>(hook)};
    return new oplink::HeatingManagerConfDocument{loaderHook};
}
