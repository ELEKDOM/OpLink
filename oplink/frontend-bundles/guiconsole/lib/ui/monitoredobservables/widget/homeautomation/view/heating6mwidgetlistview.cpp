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

#include "heating6mwidgetlistview.h"
#include "ui_heating6mwidgetlistview.h"
#include "ui/monitoredobservables/widget/buttoncmdname.h"

Heating6mWidgetListView::Heating6mWidgetListView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::heating6mWidgetListView),
    m_pwmIdx{-1}
{
    ui->setupUi(this);

    // translation ready !
    ui->energyCmd->setText(tr("Énergie"));
    ui->powerCmd->setText(tr("Puissance"));

    // create the pilot wire widget
    m_pilotWireWidget = new PilotWire6Widget;
    ui->pwmCmdLayout->addWidget(m_pilotWireWidget);

    connect(m_pilotWireWidget,SIGNAL(pilotWireOrderSelected(QString)),SLOT(onPilotWireOrderSelected(QString)));
    connect(ui->powerCmd, SIGNAL(pressed()), SLOT(onPowerCmd()));
    connect(ui->energyCmd, SIGNAL(pressed()), SLOT(onEnergyCmd()));
}

Heating6mWidgetListView::~Heating6mWidgetListView()
{
    delete ui;
}

void Heating6mWidgetListView::setTitle(const QString &title)
{
    ui->heatingName->setText(title);
}

void Heating6mWidgetListView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(propertyName)
    ui->state->setPixmap(img);
}

void Heating6mWidgetListView::setMeasVal(quint32 val)
{
    QString str;

    str.setNum(val);
    ui->v_meas->setText(str);
}

void Heating6mWidgetListView::setMeasUnit(const QString &unit)
{
    ui->u_meas->setText(unit);
}

void Heating6mWidgetListView::enableCmdButton(bool enable, const QString &cmdName)
{
    if (!enable)
    {
        m_pilotWireWidget->selectItem(cmdName);
    }
}

void Heating6mWidgetListView::onPilotWireOrderSelected(QString cmdName)
{
    emit cmdButtonClicked(cmdName);
}

void Heating6mWidgetListView::onPowerCmd()
{
    emit cmdButtonClicked(ButtonCmdName::power());
}

void Heating6mWidgetListView::onEnergyCmd()
{
    emit cmdButtonClicked(ButtonCmdName::energy());
}
