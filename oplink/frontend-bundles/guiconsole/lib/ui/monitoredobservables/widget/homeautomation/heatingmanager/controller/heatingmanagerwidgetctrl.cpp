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

#include <QRegularExpression>
#include "heatingmanagerwidgetctrl.h"
#include "observable/propertyid.h"

HeatingManagerWidgetCtrl::HeatingManagerWidgetCtrl(QString observableName,
                                                   QString observableTitle,
                                                   QString observableType,
                                                   QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation},
    m_withScheduler{false},
    m_numberOfRooms{0}
{}

HeatingManagerWidgetCtrl::~HeatingManagerWidgetCtrl()
{

}

void HeatingManagerWidgetCtrl::createStates()
{
    // declares the names of the properties being tracked for a heating manager
    //-------------------------------------------------------------------------
    addState(oplink::PropertyId::P_RUNNING);
    addState(oplink::PropertyId::P_SETPOINT);
    if (m_withScheduler)
    {
        addState(oplink::PropertyId::P_TRIGGER_MODE);
        addState(oplink::PropertyId::P_DEROGATED);
        addState(oplink::PropertyId::P_SCHEDULER_XML_DEF);
    }

    // rooms properties
    //-----------------
    for (auto i = 0; i < m_numberOfRooms; i++)
    {
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_NAME));
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_SETPOINT));
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_WCLOSED));
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_TEMPERATURE));
    }
}

void HeatingManagerWidgetCtrl::onButtonCmdClicked(QString cmdName)
{

}

MonitoredObservableWidgetView *HeatingManagerWidgetCtrl::_createView(quint8 layoutViewType)
{
    MonitoredObservableWidgetView *ret{nullptr};

    //...

    return ret;
}

void HeatingManagerWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{

}

void HeatingManagerWidgetCtrl::extractSchedulerFlagAndNumberOfRooms(QString prefix, QString heatingManagerFullType)
{
    QRegularExpression re("-([am])-(\\d+)");
    QRegularExpressionMatch match = re.match(heatingManagerFullType.remove(prefix));

    if (match.hasMatch()) {
        QString flag = match.captured(1); // scheduler flag a (automatic) > true, m (manual) > false
        QString rooms = match.captured(2); // number of rooms

        m_withScheduler = flag == "a";
        m_numberOfRooms = rooms.toUInt();
    }
}
