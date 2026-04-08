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

#include "windowsensorwidgetlistview.h"
#include "ui_windowsensorwidgetlistview.h"

WindowSensorWidgetListView::WindowSensorWidgetListView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::windowSensorWidgetListView)
{
    ui->setupUi(this);
}

WindowSensorWidgetListView::~WindowSensorWidgetListView()
{
    delete ui;
}

void WindowSensorWidgetListView::setTitle(const QString &title)
{
    ui->sensorName->setText(title);
}

void WindowSensorWidgetListView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(propertyName)
    ui->state->setPixmap(img);
}
