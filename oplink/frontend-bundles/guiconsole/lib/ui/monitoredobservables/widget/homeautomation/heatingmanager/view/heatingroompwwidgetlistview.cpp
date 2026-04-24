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

#include "heatingroompwwidgetlistview.h"

HeatingRoomPwWidgetListView::HeatingRoomPwWidgetListView(int roomNumber, QWidget *parent) :
    HeatingRoomWidgetListView{roomNumber,parent},
    m_setpointInputWidget{new PilotWireComboBox{true}}
{
    addSetpointInputWidget(m_setpointInputWidget);
    connect(m_setpointInputWidget,SIGNAL(valueChanged(QString)),SLOT(onSetpointValueChanged(QString)));
}

HeatingRoomPwWidgetListView::~HeatingRoomPwWidgetListView()
{

}

void HeatingRoomPwWidgetListView::setpointValue(const QVariant& val)
{
    m_setpointInputWidget->setValue(val.toString());
}

void HeatingRoomPwWidgetListView::onSetpointValueChanged(QString v)
{
    QVariant val{v};
    emit setpointChangedFromUi(roomNumber(),val);
}
