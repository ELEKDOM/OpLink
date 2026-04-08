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

#include "heating6mwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetlistview.h"
#include "logger/pflog.h"
#include "olfconsolelogchannel.h"

Heating6mWidgetCtrl::Heating6mWidgetCtrl(QString observableName,
                                         QString observableTitle,
                                         QString observableType,
                                         QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation},
    m_pwmComfort{":/img/comfort.png"},
    m_pwmComfort_1{":/img/comfort_1.png"},
    m_pwmComfort_2{":/img/comfort_2.png"},
    m_pwmeco{":/img/eco.png"},
    m_pwmNoFrost{":/img/nofreeze.png"},
    m_pwmStop{":/img/stop.png"}
{}

Heating6mWidgetCtrl::~Heating6mWidgetCtrl()
{

}

void Heating6mWidgetCtrl::createStates()
{
    addState(heatingModeName());
    addState(heatingMeasName());
    addState(heatingUnitName());
}

MonitoredObservableWidgetView *Heating6mWidgetCtrl::_createView(quint8 layoutViewType)
{
    Q_UNUSED(layoutViewType)
    return new Heating6mWidgetListView;
}

void Heating6mWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{
    MonitoredObservableWidgetView *heatingView{view()};

    if (heatingView)
    {
        if (heatingModeName() == propertyName)
        {
            quint8 pwm;

            pwm = value.toUInt();
            switch (pwm) {
            case 0x00:
                heatingView->setImg(m_pwmStop, "");
                heatingView->enableCmdButton(false, ButtonName::off());
                break;
            case 0x01:
                heatingView->setImg(m_pwmComfort, "");
                heatingView->enableCmdButton(false, ButtonName::comfort());
                break;
            case 0x02:
                heatingView->setImg(m_pwmComfort_1, "");
                heatingView->enableCmdButton(false, ButtonName::comfort1());
                break;
            case 0x03:
                heatingView->setImg(m_pwmComfort_2, "");
                heatingView->enableCmdButton(false, ButtonName::comfort2());
                break;
            case 0x04:
                heatingView->setImg(m_pwmeco, "");
                heatingView->enableCmdButton(false, ButtonName::eco());
                break;
            case 0x05:
                heatingView->setImg(m_pwmNoFrost, "");
                heatingView->enableCmdButton(false, ButtonName::nofrost());
                break;
            default:
                break;
            }
        }
        else if (heatingMeasName() == propertyName)
        {
            quint32 val{value.toUInt()};

            heatingView->setMeasVal(val);
        }
        else if (heatingUnitName() == propertyName)
        {
            QString val{value.toString()};

            heatingView->setMeasUnit(val);
        }
    }
}

void Heating6mWidgetCtrl::onButtonCmdClicked(QString cmdName)
{
    pfDebug4(s_OplinkGuiConsoleLogChannel) << "Heating6mWidgetCtrl::onButtonCmdClicked cmdName = " << cmdName;

    if (ButtonName::power() == cmdName || ButtonName::energy() == cmdName)
    {
        QString cmdFormat{QString("%1;%2;%3").arg(cmdName, observableName(), heatingMeasName())};

        pfDebug4(s_OplinkGuiConsoleLogChannel) << "Heating6mWidgetCtrl::onButtonCmdClicked emit " << cmdFormat;
        emit execCmd(cmdFormat);
    }
    else
    {
        QString cmdFormat{QString("set;%1;%2;%3").arg(observableName(), heatingModeName(), cmdName)};

        pfDebug4(s_OplinkGuiConsoleLogChannel) << "Heating6mWidgetCtrl::onButtonCmdClicked emit " << cmdFormat;
        emit execCmd(cmdFormat);
    }
}
