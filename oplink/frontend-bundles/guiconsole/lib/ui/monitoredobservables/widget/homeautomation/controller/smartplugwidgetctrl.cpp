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

#include "smartplugwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetview.h"

SmartPlugWidgetCtrl::SmartPlugWidgetCtrl(QString observableName,
                                         QString observableTitle,
                                         QString observableType,
                                         QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation},
    m_plugOn{":/img/plug_on.png"},
    m_plugOff{":/img/plug_off.png"}
{}

SmartPlugWidgetCtrl::~SmartPlugWidgetCtrl()
{

}

MonitoredObservableWidgetView *SmartPlugWidgetCtrl::_createView(quint8 layoutViewType)
{
    Q_UNUSED(layoutViewType)
    return new SmartPlugWidgetView;
}

void SmartPlugWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{
    MonitoredObservableWidgetView *plugView{view()};

    if (plugView)
    {
        if (output1Name() == propertyName)
        {
            bool val{value.toBool()};

            if (val)
            {
                plugView->setImg(m_plugOn, propertyName);
                plugView->enableCmdButton(true, ButtonName::off());
                plugView->enableCmdButton(false, ButtonName::on());
            }
            else
            {
                plugView->setImg(m_plugOff, propertyName);
                plugView->enableCmdButton(false, ButtonName::off());
                plugView->enableCmdButton(true, ButtonName::on());
            }
        }
        else if (measName()  == propertyName)
        {
            quint32 val{value.toUInt()};

            plugView->setMeasVal(val);
        }
        else if (unitName() == propertyName)
        {
            QString val{value.toString()};

            plugView->setMeasUnit(val);
        }
    }
}

void SmartPlugWidgetCtrl::onButtonCmdClicked(QString cmdName)
{
    if (ButtonName::on() == cmdName || ButtonName::off() == cmdName)
    {
        QString cmdFormat{QString("set;%1;%2;%3").arg(observableName(), output1Name(), cmdName)};

        emit execCmd(cmdFormat);
    }
    else
    {
        QString cmdFormat{QString("%1;%2").arg(cmdName, observableName())};

        emit execCmd(cmdFormat);
    }
}
