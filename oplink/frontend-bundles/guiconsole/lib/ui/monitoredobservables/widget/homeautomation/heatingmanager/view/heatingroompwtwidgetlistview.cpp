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

#include "heatingroompwtwidgetlistview.h"

HeatingRoomPwtWidgetListView::HeatingRoomPwtWidgetListView(int roomNumber, QWidget *parent):
    HeatingRoomWidgetListView{roomNumber,parent},
    m_setpointInputWidget{new TempDoubleSpinBox}
{
    addSetpointInputWidget(m_setpointInputWidget);
    connect(m_setpointInputWidget,SIGNAL(valueChanged(double)),SLOT(onSetpointValueChanged(double)));
}

HeatingRoomPwtWidgetListView::~HeatingRoomPwtWidgetListView()
{

}

void HeatingRoomPwtWidgetListView::setpointValue(const QVariant& val)
{
    m_setpointInputWidget->setValue(val.toDouble());
}

void HeatingRoomPwtWidgetListView::onSetpointValueChanged(double d)
{
    QVariant val{d};
    emit setpointChangedFromUi(roomNumber(),val);
}
