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


#include "temperaturehumiditywidgetctrl.h"
#include "ui/monitoredobservables/widget/view/temperaturehumiditywidgetview.h"

using namespace elekdom::oplink::frontend::guiconsole::monitoredobservable::widget;

TemperatureHumidityWidgetCtrl::TemperatureHumidityWidgetCtrl(QString observableName,
                                                             QString observableTitle,
                                                             QString observableType,
                                                             QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation}
{}

TemperatureHumidityWidgetCtrl::~TemperatureHumidityWidgetCtrl()
{

}

MonitoredObservableWidgetView *TemperatureHumidityWidgetCtrl::_createView(quint8 layoutViewType)
{
    Q_UNUSED(layoutViewType)
    return new TemperatureHumidityWidgetView;
}

void TemperatureHumidityWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{
    MonitoredObservableWidgetView *plugView{view()};

    if (plugView)
    {
        double val{value.toDouble()};

        if (temperatureName()  == propertyName)
        {
            plugView->setVal(0, val);
        }
        else if (humidityName()  == propertyName)
        {
            plugView->setVal(1, val);
        }
    }
}

void TemperatureHumidityWidgetCtrl::onButtonCmdClicked(QString cmdName)
{
    Q_UNUSED(cmdName)
}
