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

#include "smartplugwidgetlistview.h"
#include "ui_smartplugwidgetlistview.h"
#include "ui/monitoredobservables/widget/buttoncmdname.h"

SmartPlugWidgetListView::SmartPlugWidgetListView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::smartPlugWidgetListView)
{
    ui->setupUi(this);

    // translation ready !
    // translation ready !
    ui->onCmd->setText(tr("activer"));
    ui->offCmd->setText(tr("désactiver"));
    ui->energyCmd->setText(tr("Énergie"));
    ui->powerCmd->setText(tr("Puissance"));

    connect(ui->onCmd, SIGNAL(pressed()), SLOT(onOnCmd()));
    connect(ui->offCmd, SIGNAL(pressed()), SLOT(onOffCmd()));
    connect(ui->powerCmd, SIGNAL(pressed()), SLOT(onPowerCmd()));
    connect(ui->energyCmd, SIGNAL(pressed()), SLOT(onEnergyCmd()));
}

SmartPlugWidgetListView::~SmartPlugWidgetListView()
{
    delete ui;
}

void SmartPlugWidgetListView::setTitle(const QString &title)
{
    ui->plugName->setText(title);
}

void SmartPlugWidgetListView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(propertyName)
    ui->state->setPixmap(img);
}

void SmartPlugWidgetListView::setMeasVal(quint32 val)
{
    QString str;

    str.setNum(val);
    ui->v_meas->setText(str);
}

void SmartPlugWidgetListView::setMeasUnit(const QString &unit)
{
     ui->u_meas->setText(unit);
}

void SmartPlugWidgetListView::enableCmdButton(bool enable, const QString &cmdName)
{
    if (ButtonCmdName::on() == cmdName)
    {
        ui->onCmd->setEnabled(enable);
    }
    else if (ButtonCmdName::off() == cmdName)
    {
        ui->offCmd->setEnabled(enable);
    }
    else if (ButtonCmdName::power() == cmdName)
    {
        ui->powerCmd->setEnabled(enable);
    }
    else if (ButtonCmdName::energy() == cmdName)
    {
        ui->energyCmd->setEnabled(enable);
    }
}

void SmartPlugWidgetListView::onOnCmd()
{
    emit cmdButtonClicked(ButtonCmdName::on());
}

void SmartPlugWidgetListView::onOffCmd()
{
    emit cmdButtonClicked(ButtonCmdName::off());
}

void SmartPlugWidgetListView::onPowerCmd()
{
    emit cmdButtonClicked(ButtonCmdName::power());
}

void SmartPlugWidgetListView::onEnergyCmd()
{
    emit cmdButtonClicked(ButtonCmdName::energy());
}
