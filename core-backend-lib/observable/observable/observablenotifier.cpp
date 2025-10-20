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

#include "observablenotifier.h"
#include "logger/pflog.h"
#include "observable/observablelogchannel.h"

oplink::ObservableNotifier::ObservableNotifier(QObject *parent) : QObject(parent)
{

}

oplink::ObservableNotifier::~ObservableNotifier()
{

}

bool oplink::ObservableNotifier::subscribe(ObservableSubscriber *subscriber)
{
    bool ok{true};

    ok = connect(this ,
                 SIGNAL(stateChange(oplink::ObservableName,oplink::PropertyName,QVariant)),
                 subscriber,
                 SLOT(onStateChange(oplink::ObservableName,oplink::PropertyName,QVariant)),
                 Qt::QueuedConnection);
    if (!ok)
    {
        pfErr(s_ObservableLogChannel) << tr("--GacObservableNotifier connect signal stateChange : échec");
    }

    return ok;
}

bool oplink::ObservableNotifier::unsubscribe(ObservableSubscriber *subscriber)
{
    bool ok = disconnect(this ,
                         SIGNAL(stateChange(oplink::ObservableName,oplink::PropertyName,QVariant)),
                         subscriber,
                         SLOT(onStateChange(oplink::ObservableName,oplink::PropertyName,QVariant)));
    if (!ok)
    {
        pfWarning1(s_ObservableLogChannel) << tr("--GacObservableNotifier disconnect signal stateChange : échec");
    }

    return ok;
}

void oplink::ObservableNotifier::notifyPropertyValueChange(oplink::ObservableName observableName,
                                                           oplink::PropertyName propertyName,
                                                           QVariant propertyValue)
{
    emit stateChange(observableName, propertyName, propertyValue);
}
