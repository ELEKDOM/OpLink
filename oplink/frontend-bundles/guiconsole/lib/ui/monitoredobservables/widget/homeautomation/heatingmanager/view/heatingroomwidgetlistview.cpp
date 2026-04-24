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

#include "heatingroomwidgetlistview.h"
#include "ui_heatingroomwidgetlistview.h"
#include "observable/propertyid.h"

HeatingRoomWidgetListView::HeatingRoomWidgetListView(int roomNumber, QWidget *parent):
    QWidget{parent},
    m_roomNumber{roomNumber},
    ui{new Ui::heatingRoomWidgetListView}
{
    ui->setupUi(this);
}

HeatingRoomWidgetListView::~HeatingRoomWidgetListView()
{
}

void HeatingRoomWidgetListView::setRoomName(const QString &roomName)
{
    ui->roomName->setText(roomName);
}

void HeatingRoomWidgetListView::setImg(const QPixmap &img, const QString &propertyName)
{
    if (oplink::PropertyId::P_WCLOSED == propertyName)
    {
        ui->closedAggregat->setPixmap(img);
    }
}

void HeatingRoomWidgetListView::setTemperature(double value)
{
    QString str;

    str.setNum(value, 'f', 2);
    ui->lastTemp->setText(str);
}

void HeatingRoomWidgetListView::addSetpointInputWidget(QWidget *inputWidget)
{
    ui->setpointAreaLayout->addWidget(inputWidget);
}