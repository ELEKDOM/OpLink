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

#include "monitoredobservablewidgetctrl.h"
#include "ui/monitoredobservables/widget/view/monitoredobservablewidgetview.h"

MonitoredObservableWidgetCtrl::MonitoredObservableWidgetCtrl(QString observableName,
                                                             QString observableTitle,
                                                             QString observableType,
                                                             QString observableLocalisation,
                                                             QObject *parent):
    QObject{parent},
    m_observableName{observableName},
    m_observableTitle{observableTitle},
    m_observableType{observableType},
    m_observableLocalisation{observableLocalisation},
    m_view{nullptr}
{

}

MonitoredObservableWidgetCtrl::~MonitoredObservableWidgetCtrl()
{
}

MonitoredObservableWidgetView *MonitoredObservableWidgetCtrl::createView(quint8 layoutViewType)
{
    m_view = _createView(layoutViewType);
    m_view->setTitle(m_observableTitle);
    connect(m_view,SIGNAL(cmdButtonClicked(QString)),SLOT(onButtonCmdClicked(QString)));
    return m_view;
}

void MonitoredObservableWidgetCtrl::addState(const QString &propertyName)
{
    m_monitoredStates.insert(propertyName, true);
}

void MonitoredObservableWidgetCtrl::updateStateValue(const QString &propertyName, const QVariant &value)
{
    if (m_monitoredStates.contains(propertyName))
    {
        _updateStateValue(propertyName,value);
    }
}
