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

#include "heating6mwidgetview.h"
#include "ui_heating6mwidgetview.h"

Heating6mWidgetView::Heating6mWidgetView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::heating6mWidgetView),
    m_pwmIdx{-1}
{
    ui->setupUi(this);

    ui->pwmCmd->addItem("comfort", ButtonName::comfort());
    ui->pwmCmd->addItem("comfort - 1", ButtonName::comfort1());
    ui->pwmCmd->addItem("comfort - 2", ButtonName::comfort2());
    ui->pwmCmd->addItem("eco", ButtonName::eco());
    ui->pwmCmd->addItem("no frost", ButtonName::nofrost());
    ui->pwmCmd->addItem("stop", ButtonName::off());

    connect(ui->pwmCmd, SIGNAL(activated(int)), SLOT(onItemPwmCmd(int)));
    connect(ui->powerCmd, SIGNAL(pressed()), SLOT(onPowerCmd()));
    connect(ui->energyCmd, SIGNAL(pressed()), SLOT(onEnergyCmd()));
}

Heating6mWidgetView::~Heating6mWidgetView()
{
    delete ui;
}

void Heating6mWidgetView::setTitle(const QString &title)
{
    ui->heatingName->setText(title);
}

void Heating6mWidgetView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(propertyName)
    ui->state->setPixmap(img);
}

void Heating6mWidgetView::setMeasVal(quint32 val)
{
    QString str;

    str.setNum(val);
    ui->v_meas->setText(str);
}

void Heating6mWidgetView::setMeasUnit(const QString &unit)
{
    ui->u_meas->setText(unit);
}

void Heating6mWidgetView::enableCmdButton(bool enable, const QString &cmdName)
{
    if (!enable)
    {
        if ((m_pwmIdx = ui->pwmCmd->findData(cmdName)) != -1)
        {
            ui->pwmCmd->setCurrentIndex(m_pwmIdx);
        }
    }
}

void Heating6mWidgetView::onItemPwmCmd(int index)
{
    if (index != m_pwmIdx)
    {
        QVariant cmdArg{ui->pwmCmd->itemData(index)};

        emit cmdButtonClicked(cmdArg.toString());
    }
}

void Heating6mWidgetView::onPowerCmd()
{
    emit cmdButtonClicked(ButtonName::power());
}

void Heating6mWidgetView::onEnergyCmd()
{
    emit cmdButtonClicked(ButtonName::energy());
}
