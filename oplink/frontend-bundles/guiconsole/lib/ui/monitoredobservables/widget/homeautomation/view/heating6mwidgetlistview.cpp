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

Heating6mWidgetListView::Heating6mWidgetListView(QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui(new Ui::heating6mWidgetListView),
    m_pwmIdx{-1}
{
    ui->setupUi(this);

    ui->pwmCmd->addItem(tr("confort"), ButtonCmdName::comfort());
    ui->pwmCmd->addItem(tr("confort - 1"), ButtonCmdName::comfort1());
    ui->pwmCmd->addItem(tr("confort - 2"), ButtonCmdName::comfort2());
    ui->pwmCmd->addItem(tr("eco"), ButtonCmdName::eco());
    ui->pwmCmd->addItem(tr("hors gel"), ButtonCmdName::nofrost());
    ui->pwmCmd->addItem(tr("arrêt"), ButtonCmdName::off());

    connect(ui->pwmCmd, SIGNAL(activated(int)), SLOT(onItemPwmCmd(int)));
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
        if ((m_pwmIdx = ui->pwmCmd->findData(cmdName)) != -1)
        {
            ui->pwmCmd->setCurrentIndex(m_pwmIdx);
        }
    }
}

void Heating6mWidgetListView::onItemPwmCmd(int index)
{
    if (index != m_pwmIdx)
    {
        QVariant cmdArg{ui->pwmCmd->itemData(index)};

        emit cmdButtonClicked(cmdArg.toString());
    }
}

void Heating6mWidgetListView::onPowerCmd()
{
    emit cmdButtonClicked(ButtonCmdName::power());
}

void Heating6mWidgetListView::onEnergyCmd()
{
    emit cmdButtonClicked(ButtonCmdName::energy());
}
