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

#ifndef WINDOWSENSORWIDGETCTRL_H
#define WINDOWSENSORWIDGETCTRL_H

#include <QPixmap>
#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"

///
/// \brief The WindowSensorWidgetCtrl class
/// widget associated with the "window_sensor" model defined on the backend
///
class WindowSensorWidgetCtrl : public MonitoredObservableWidgetCtrl
{
private:
    static QString closedName() {return QStringLiteral("closed");}

public:
    WindowSensorWidgetCtrl(QString observableName,
                           QString observableTitle,
                           QString observableType,
                           QString observableLocalisation);
    ~WindowSensorWidgetCtrl() override;

protected:
    void createStates() override;
    MonitoredObservableWidgetView *_createView(quint8 layoutViewType) override;
    void _updateStateValue(const QString &propertyName,
                           const QVariant &value) override;
    void onButtonCmdClicked(QString cmdName) override;

private:
    QPixmap m_open;
    QPixmap m_closed;
};

#endif // WINDOWSENSORWIDGETCTRL_H
