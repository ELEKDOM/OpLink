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

#ifndef HEATINGMANAGERWIDGETCTRL_H
#define HEATINGMANAGERWIDGETCTRL_H


#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"

class HeatingManagerWidgetCtrl : public MonitoredObservableWidgetCtrl
{
public:
    HeatingManagerWidgetCtrl(QString observableName,
                             QString observableTitle,
                             QString observableType,
                             QString observableLocalisation);
    ~HeatingManagerWidgetCtrl() override;

protected:
    void createStates() override;
    void onButtonCmdClicked(QString cmdName) override;
    MonitoredObservableWidgetView *_createView(quint8 layoutViewType) override;
    void _updateStateValue(const QString &propertyName,
                           const QVariant &value) override;

protected:
    void extractSchedulerFlagAndNumberOfRooms(QString prefix, QString heatingManagerFullType);

private:
    bool m_withScheduler;
    int  m_numberOfRooms;
};

#endif // HEATINGMANAGERWIDGETCTRL_H
