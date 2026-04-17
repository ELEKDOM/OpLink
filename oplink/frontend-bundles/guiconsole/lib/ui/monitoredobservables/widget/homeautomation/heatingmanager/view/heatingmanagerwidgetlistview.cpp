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

#include "heatingmanagerwidgetlistview.h"
#include "ui_heatingmanagerwidgetlistview.h"
#include "heatingroomwidgetlistview.h"
#include "observable/propertyid.h"

HeatingManagerWidgetListView::HeatingManagerWidgetListView(bool withScheduler,QWidget *parent):
    MonitoredObservableWidgetListView{parent},
    ui{new Ui::heatingManagerWidgetListView}
{
    ui->setupUi(this);

    // translation ready !
    ui->onLabel->setText(tr("marche"));
    ui->offLabel->setText(tr("arrêt"));
    ui->triggerModeGroupBox->setTitle(tr("Déclenchement"));
    ui->onDemandCheckBox->setText(tr("à la demande"));
    ui->plannedCheckBox->setText(tr("planifié"));

    // need scheduler view ?
    if (!withScheduler)
    {
        ui->onDemandCheckBox->setChecked(true);
        ui->plannedCheckBox->setEnabled(false);
        ui->verticalLayout_2->removeWidget(ui->derogatedStatusArea);
        delete ui->derogatedStatusArea;
    }

    // Signals/Slots
    //--------------
    connect(ui->onOffSlider,SIGNAL(valueChanged(int)),SLOT(onOnOffSliderValueChanged(int)));
    connect(ui->onDemandCheckBox,SIGNAL(toggled(bool)),SLOT(onOnDemandToggled(bool)));
    connect(ui->plannedCheckBox,SIGNAL(toggled(bool)),SLOT(onPlannedToggled(bool)));
}

HeatingManagerWidgetListView::~HeatingManagerWidgetListView()
{

}

void HeatingManagerWidgetListView::setRoomName(quint8 roomNumber, const QString &roomName)
{
    ui_rooms[roomNumber - 1]->setRoomName(roomName);
}

void HeatingManagerWidgetListView::setRoomSetpoint(quint8 roomNumber, const QVariant& value)
{
    ui_rooms[roomNumber - 1]->setpointValue(value);
}

void HeatingManagerWidgetListView::setRoomImg(quint8 roomNumber, const QPixmap &img, const QString &propertyName)
{
    ui_rooms[roomNumber - 1]->setImg(img,propertyName);
}

void HeatingManagerWidgetListView::setRoomTemperature(quint8 roomNumber, double value)
{
    ui_rooms[roomNumber - 1]->setTemperature(value);
}

void HeatingManagerWidgetListView::setTitle(const QString &title)
{
    ui->managerTitle->setText(title);
}

void HeatingManagerWidgetListView::enableCmdButton(bool enable, const QString &cmdName)
{
    if (ButtonCmdName::managerOnOff() == cmdName)
    {
        if (enable)
        {
            enableManagerView(true);
            ui->onOffSlider->setStyleSheet("::groove:horizontal{ background : green}");
            ui->onLabel->setStyleSheet("color:green");
            ui->offLabel->setStyleSheet("");
        }
        else
        {
            enableManagerView(false);
            ui->onOffSlider->setStyleSheet("::groove:horizontal{ background : red}");
            ui->offLabel->setStyleSheet("color:red");
            ui->onLabel->setStyleSheet("");
        }
    }
    else if (ButtonCmdName::triggerPlannedMode() == cmdName)
    {
        if (enable)
        {
            ui->plannedCheckBox->setChecked(true);
        }
        else
        {
            ui->onDemandCheckBox->setChecked(true);
        }
    }
    /*
    else if (ButtonCmdName:: == cmdName)
    {

    }
    */
}

void HeatingManagerWidgetListView::setImg(const QPixmap &img, const QString &propertyName)
{
    if (oplink::PropertyId::P_DEROGATED == propertyName)
    {
        ui->derogatedStatusArea->setPixmap(img);
    }
}

void HeatingManagerWidgetListView::addSetpointInputWidget(QWidget *inputWidget)
{
    ui->setpointAreaLayout->addWidget(inputWidget);
}

QWidget *HeatingManagerWidgetListView::heatingManagerWidgetContent()
{
    return ui->heatingManagerWidgetContent;
}

QVBoxLayout *HeatingManagerWidgetListView::contentVerticalLayout()
{
    return ui->contentVerticalLayout;
}

void HeatingManagerWidgetListView::onOnOffSliderValueChanged(int value)
{
    if (0 == value)
    {
        // off
        emit cmdButtonClicked(ButtonCmdName::managerOff());
    }
    else if (1 == value)
    {
        // on
        emit cmdButtonClicked(ButtonCmdName::managerOn());
    }
}

void HeatingManagerWidgetListView::onPlannedToggled(bool checked)
{
    if (checked)
    {
        emit cmdButtonClicked(ButtonCmdName::plannedMode());
    }
}

void HeatingManagerWidgetListView::onOnDemandToggled(bool checked)
{
    if (checked)
    {
        emit cmdButtonClicked(ButtonCmdName::onDemandMode());
    }
}

void HeatingManagerWidgetListView::enableManagerView(bool enable)
{
    ui->setpointTriggerArea->setEnabled(enable);
    enableRoomsView(enable);
}

void HeatingManagerWidgetListView::enableRoomsView(bool enable)
{
    for (auto i = 0;i < ui_rooms.size();i++)
    {
        ui_rooms[i]->setEnabled(enable);
    }
}


