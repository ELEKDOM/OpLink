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

#include "temperaturehumiditywidgetview.h"
#include "ui_temperaturehumiditywidgetview.h"

TemperatureHumidityWidgetView::TemperatureHumidityWidgetView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::temperatureHumidityWidgetView)
{
    ui->setupUi(this);
}

TemperatureHumidityWidgetView::~TemperatureHumidityWidgetView()
{
    delete ui;
}

void TemperatureHumidityWidgetView::setTitle(const QString &title)
{
     ui->sensorName->setText(title);
}

void TemperatureHumidityWidgetView::setVal(quint8 idx, double val)
{
    QLabel *label{nullptr};

    if (0 == idx)
    {
        label = ui->v_temperature;
    }
    else if (1 == idx)
    {
        label = ui->v_humidity;
    }

    if (label)
    {
        QString str;

        str.setNum(val, 'f', 2);
        label->setText(str);
    }
}
