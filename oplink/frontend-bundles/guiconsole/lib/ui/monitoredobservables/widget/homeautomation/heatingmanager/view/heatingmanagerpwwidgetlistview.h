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

#ifndef HEATINGMANAGERPWWIDGETLISTVIEW_H
#define HEATINGMANAGERPWWIDGETLISTVIEW_H

#include "ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerwidgetlistview.h"
#include "ui/monitoredobservables/widget/homeautomation/view/pilotwirecombobox.h"

class HeatingManagerPwWidgetListView : public HeatingManagerWidgetListView
{
    Q_OBJECT

public:
    explicit HeatingManagerPwWidgetListView(bool withScheduler,int nbOfRooms,QWidget *parent = nullptr);
    ~HeatingManagerPwWidgetListView() override;

protected:
    void setSetpointVal(const QVariant& value) override;

private slots:
    void onSetpointValueChanged(QString s);

private:
    PilotWireComboBox *m_setpointInputWidget;
};

#endif // HEATINGMANAGERPWWIDGETLISTVIEW_H
