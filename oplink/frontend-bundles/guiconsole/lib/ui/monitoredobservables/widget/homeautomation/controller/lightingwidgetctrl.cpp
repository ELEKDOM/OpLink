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

#include "lightingwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/view/lightingwidgetview.h"

LightingWidgetCtrl::LightingWidgetCtrl(QString observableName,
                                       QString observableTitle,
                                       QString observableType,
                                       QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation},
    m_lightOn{":/img/light_on.png"},
    m_lightOff{":/img/light_off.png"}
{}

LightingWidgetCtrl::~LightingWidgetCtrl()
{

}

MonitoredObservableWidgetView *LightingWidgetCtrl::_createView(quint8 layoutViewType)
{
    Q_UNUSED(layoutViewType)
    return new LightingWidgetView;
}

void LightingWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{
    if (stateName() == propertyName)
    {
        bool val{value.toBool()};
        MonitoredObservableWidgetView *lightingView{view()};

        if (lightingView)
        {
            if (val)
            {
                lightingView->setImg(m_lightOn, propertyName);
                lightingView->enableCmdButton(true, ButtonName::off());
                lightingView->enableCmdButton(false, ButtonName::on());
            }
            else
            {
                lightingView->setImg(m_lightOff, propertyName);
                lightingView->enableCmdButton(false, ButtonName::off());
                lightingView->enableCmdButton(true, ButtonName::on());
            }
        }
    }
}

void LightingWidgetCtrl::onButtonCmdClicked(QString cmdName)
{
    if (cmdName == ButtonName::on() || cmdName == ButtonName::off())
    {
        QString cmdFormat{QString("set;%1;%2;%3").arg(observableName(), stateName(), cmdName)};

        emit execCmd(cmdFormat);
    }
}
