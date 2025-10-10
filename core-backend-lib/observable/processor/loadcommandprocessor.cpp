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

using namespace elekdom::oplink::core::observable;

LoadCommandProcessor::LoadCommandProcessor(const Observable& observable,
                                                 const command::CommandName& cmdName):
    LowCommandProcessor{observable, cmdName}
{

}

LoadCommandProcessor::~LoadCommandProcessor()
{

}

void LoadCommandProcessor::process(command::QspCommand order)
{
    PropertyName targetPropertyName{order->property()};
    const Observable& myObservable{observable()};

    QspProperty targetProperty{myObservable.property(targetPropertyName)};
    QspLoadProperty targetLoadProperty{targetProperty.dynamicCast<LoadProperty>()};

    if (!targetLoadProperty.isNull())
    {
        QspOperationDeviceProperty relatedMasterProperty{targetLoadProperty->master()};
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
