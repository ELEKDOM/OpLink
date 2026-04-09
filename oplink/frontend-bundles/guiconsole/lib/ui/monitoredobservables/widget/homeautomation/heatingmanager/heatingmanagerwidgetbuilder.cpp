// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#include "heatingmanagerwidgetbuilder.h"
#include "observable/heatingmanagermodelnames.h"
#include "ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerpwtwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerpwwidgetctrl.h"

HeatingManagerWidgetBuilder::HeatingManagerWidgetBuilder() {}

HeatingManagerWidgetBuilder::~HeatingManagerWidgetBuilder()
{

}

MonitoredObservableWidgetCtrl *HeatingManagerWidgetBuilder::createWidget(QString observableName, QString observableTitle, QString observableType, QString observableLocalisation)
{
    MonitoredObservableWidgetCtrl *ret{nullptr};

    if (observableType.contains(oplink::HeatingManagerModelNames::pilotWireThermostatModelName()))
    {
        ret = createHeatingManagerPwThermostatWidget(observableName,
                                                     observableTitle,
                                                     observableType,
                                                     observableLocalisation);
    }
    else if (observableType.contains(oplink::HeatingManagerModelNames::pilotWireModelName()))
    {
        ret = createHeatingManagerPwWidget(observableName,
                                           observableTitle,
                                           observableType,
                                           observableLocalisation);
    }

    return ret;
}

MonitoredObservableWidgetCtrl *HeatingManagerWidgetBuilder::createHeatingManagerPwWidget(QString observableName,
                                                                                         QString observableTitle,
                                                                                         QString observableType,
                                                                                         QString observableLocalisation)
{
    return new HeatingManagerPwWidgetCtrl(observableName,
                                          observableTitle,
                                          observableType,
                                          observableLocalisation);
}

MonitoredObservableWidgetCtrl *HeatingManagerWidgetBuilder::createHeatingManagerPwThermostatWidget(QString observableName,
                                                                                                   QString observableTitle,
                                                                                                   QString observableType,
                                                                                                   QString observableLocalisation)
{
    return new HeatingManagerPwtWidgetCtrl(observableName,
                                          observableTitle,
                                          observableType,
                                          observableLocalisation);
}

QString HeatingManagerWidgetBuilder::getFamilyName(const QString &observableType)
{
    QString ret;

    //...

    return ret;
}
