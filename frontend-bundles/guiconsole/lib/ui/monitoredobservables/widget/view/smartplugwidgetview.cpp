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

#include "smartplugwidgetview.h"
#include "ui_smartplugwidgetview.h"

SmartPlugWidgetView::SmartPlugWidgetView(QWidget *parent):
    WidgetListView{parent},
    ui(new Ui::smartPlugWidgetView)
{
    ui->setupUi(this);

    connect(ui->onCmd, SIGNAL(pressed()), SLOT(onOnCmd()));
    connect(ui->offCmd, SIGNAL(pressed()), SLOT(onOffCmd()));
    connect(ui->powerCmd, SIGNAL(pressed()), SLOT(onPowerCmd()));
    connect(ui->energyCmd, SIGNAL(pressed()), SLOT(onEnergyCmd()));
}

SmartPlugWidgetView::~SmartPlugWidgetView()
{
    delete ui;
}

void SmartPlugWidgetView::setTitle(const QString &title)
{
    ui->plugName->setText(title);
}

void SmartPlugWidgetView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(propertyName)
    ui->state->setPixmap(img);
}

void SmartPlugWidgetView::setMeasVal(quint32 val)
{
    QString str;

    str.setNum(val);
    ui->v_meas->setText(str);
}

void SmartPlugWidgetView::setMeasUnit(const QString &unit)
{
     ui->u_meas->setText(unit);
}

void SmartPlugWidgetView::enableCmdButton(bool enable, const QString &cmdName)
{
    if (ButtonName::on() == cmdName)
    {
        ui->onCmd->setEnabled(enable);
    }
    else if (ButtonName::off() == cmdName)
    {
        ui->offCmd->setEnabled(enable);
    }
    else if (ButtonName::power() == cmdName)
    {
        ui->powerCmd->setEnabled(enable);
    }
    else if (ButtonName::energy() == cmdName)
    {
        ui->energyCmd->setEnabled(enable);
    }
}

void SmartPlugWidgetView::onOnCmd()
{
    emit cmdButtonClicked(ButtonName::on());
}

void SmartPlugWidgetView::onOffCmd()
{
    emit cmdButtonClicked(ButtonName::off());
}

void SmartPlugWidgetView::onPowerCmd()
{
    emit cmdButtonClicked(ButtonName::power());
}

void SmartPlugWidgetView::onEnergyCmd()
{
    emit cmdButtonClicked(ButtonName::energy());
}
