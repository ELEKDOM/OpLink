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

#include "heatingmanagerpwtwidgetlistview.h"
#include "heatingroompwtwidgetlistview.h"

HeatingManagerPwtWidgetListView::HeatingManagerPwtWidgetListView(bool withScheduler, int nbOfRooms, QWidget *parent):
    HeatingManagerWidgetListView{withScheduler,parent}
{
    // Create the specific widget to manage the setpoint value.
    // For a thermostat the setpoint is a temperature value !
    m_setpointInputWidget = new TempDoubleSpinBox;
    addSetpointInputWidget(m_setpointInputWidget);

    // to manage setpoint change from ui
    connect(m_setpointInputWidget,SIGNAL(valueChanged(double)),SLOT(onSetpointValueChanged(double)));

    // Rooms area
    for (auto i = 0;i < nbOfRooms;i++)
    {
        HeatingRoomWidgetListView *newRoom{new HeatingRoomPwtWidgetListView(i+1,heatingManagerWidgetContent())};
        contentVerticalLayout()->addWidget(newRoom);
        ui_rooms.append(newRoom);
        connect(newRoom,SIGNAL(setpointChangedFromUi(int,QVariant)),SIGNAL(roomSetpointChangedFromUi(int,QVariant)));
    }
    contentVerticalLayout()->addStretch();
}

HeatingManagerPwtWidgetListView::~HeatingManagerPwtWidgetListView()
{

}

void HeatingManagerPwtWidgetListView::setSetpointVal(const QVariant &value)
{
    m_setpointInputWidget->setValue(value.toDouble());
}

void HeatingManagerPwtWidgetListView::onSetpointValueChanged(double d)
{
    QVariant val{d};

    emit setpointChangedFromUi(val);
}
