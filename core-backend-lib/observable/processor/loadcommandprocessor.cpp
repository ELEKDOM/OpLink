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

#include "logger/pflog.h"
#include "loadcommandprocessor.h"
#include "command/command.h"
#include "observable/property/property.h"
#include "observable/property/loadproperty.h"
#include "observable/property/operationdeviceproperty.h"
#include "observable/observable/observable.h"

oplink::LoadCommandProcessor::LoadCommandProcessor(const oplink::Observable& observable,
                                                   const oplink::CommandName& cmdName):
    LowCommandProcessor{observable, cmdName}
{

}

oplink::LoadCommandProcessor::~LoadCommandProcessor()
{

}

void oplink::LoadCommandProcessor::process(oplink::QspCommand order)
{
    oplink::PropertyName targetPropertyName{order->property()};
    const oplink::Observable& myObservable{observable()};

    oplink::QspProperty targetProperty{myObservable.property(targetPropertyName)};
    oplink::QspLoadProperty targetLoadProperty{targetProperty.dynamicCast<oplink::LoadProperty>()};

    if (!targetLoadProperty.isNull())
    {
        oplink::QspOperationDeviceProperty relatedMasterProperty{targetLoadProperty->master()};
        Observable& relatedMasterObservable{relatedMasterProperty->observable()};

        //Redirect order
        order->replaceTarget(relatedMasterObservable.name(), relatedMasterProperty->name());
        relatedMasterObservable.process(order);
    }
    else
    {
        pfWarning3(logChannel()) << QObject::tr("Il faut une propriété cible dans la commande : %1").arg(order->name());
    }
}
