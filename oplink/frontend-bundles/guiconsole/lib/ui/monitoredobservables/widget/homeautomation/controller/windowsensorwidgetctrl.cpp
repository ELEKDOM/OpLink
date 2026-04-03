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

#include "windowsensorwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetview.h"

WindowSensorWidgetCtrl::WindowSensorWidgetCtrl(QString observableName,
                                               QString observableTitle,
                                               QString observableType,
                                               QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation},
    m_open{":/img/window_open.png"},
    m_closed{":/img/window_closed.png"}
{}

WindowSensorWidgetCtrl::~WindowSensorWidgetCtrl()
{

}

void WindowSensorWidgetCtrl::createStates()
{
    addState(closedName());
}

MonitoredObservableWidgetView *WindowSensorWidgetCtrl::_createView(quint8 layoutViewType)
{
    Q_UNUSED(layoutViewType)
    return new WindowSensorWidgetView;
}

void WindowSensorWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{
    if (closedName() == propertyName)
    {
        MonitoredObservableWidgetView *windowSensorView{view()};
        if (windowSensorView)
        {
            bool val{value.toBool()};
            if (val)
            {
                windowSensorView->setImg(m_closed, propertyName);
            }
            else
            {
                windowSensorView->setImg(m_open, propertyName);
            }
        }
    }

}

void WindowSensorWidgetCtrl::onButtonCmdClicked(QString cmdName)
{
    Q_UNUSED(cmdName)
}
