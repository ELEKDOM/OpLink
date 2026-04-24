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

#include "heatingmanagerpwwidgetlistview.h"
#include "heatingroompwwidgetlistview.h"

HeatingManagerPwWidgetListView::HeatingManagerPwWidgetListView(bool withScheduler, int nbOfRooms, QWidget *parent):
    HeatingManagerWidgetListView{withScheduler,parent}
{
    // Create the specific widget to manage the setpoint value.
    // For a pilot wire central is a 6 order value !
    m_setpointInputWidget = new PilotWireComboBox(true);
    addSetpointInputWidget(m_setpointInputWidget);

    // to manage setpoint change from ui
    connect(m_setpointInputWidget,SIGNAL(valueChanged(QString)),SLOT(onSetpointValueChanged(QString)));

    // Rooms area
    for (auto i = 0;i < nbOfRooms;i++)
    {
        HeatingRoomWidgetListView *newRoom{new HeatingRoomPwWidgetListView(i+1,heatingManagerWidgetContent())};
        contentVerticalLayout()->addWidget(newRoom);
        ui_rooms.append(newRoom);
        connect(newRoom,SIGNAL(setpointChangedFromUi(int,QVariant)),SIGNAL(roomSetpointChangedFromUi(int,QVariant)));
    }
    contentVerticalLayout()->addStretch();
}

HeatingManagerPwWidgetListView::~HeatingManagerPwWidgetListView()
{

}

void HeatingManagerPwWidgetListView::setSetpointVal(const QVariant &value)
{
    m_setpointInputWidget->setValue(value.toString());
}

void HeatingManagerPwWidgetListView::onSetpointValueChanged(QString s)
{
    QVariant val{s};

    emit setpointChangedFromUi(val);
}
