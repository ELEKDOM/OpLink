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

#include <QRegularExpression>
#include "heatingmanagerwidgetctrl.h"
#include "observable/propertyid.h"
#include "observable/values.h"
#include "command/command-names.h"
#include "ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerwidgetlistview.h"

HeatingManagerWidgetCtrl::HeatingManagerWidgetCtrl(QString observableName,
                                                   QString observableTitle,
                                                   QString observableType,
                                                   QString observableLocalisation):
    MonitoredObservableWidgetCtrl{observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation},
    m_withScheduler{false},
    m_numberOfRooms{0},
    m_derogatedImg{":/img/hm_derogated.png"},
    m_plannedImg{":/img/hm_planned.png"},
    m_onDemandImg{":/img/hm_ondemand.png"},
    m_wOpen{":/img/window_open.png"},
    m_wClosed{":/img/window_closed.png"}
{}

HeatingManagerWidgetCtrl::~HeatingManagerWidgetCtrl()
{

}

void HeatingManagerWidgetCtrl::extendedConnect()
{
    HeatingManagerWidgetListView *managerView{dynamic_cast<HeatingManagerWidgetListView*>(view())};

    connect(managerView,SIGNAL(setpointChangedFromUi(QVariant)),SLOT(onSetpointChangedFromUi(QVariant)));
    connect(managerView,SIGNAL(roomSetpointChangedFromUi(int,QVariant)),SLOT(onRoomSetpointChangedFromUi(int,QVariant)));
}

void HeatingManagerWidgetCtrl::createStates()
{
    // declares the names of the properties being tracked for a heating manager
    //-------------------------------------------------------------------------
    addState(oplink::PropertyId::P_RUNNING);
    addState(oplink::PropertyId::P_SETPOINT);
    if (m_withScheduler)
    {
        addState(oplink::PropertyId::P_TRIGGER_MODE);
        addState(oplink::PropertyId::P_DEROGATED);
        addState(oplink::PropertyId::P_SCHEDULER_XML_DEF);
    }

    // rooms properties
    //-----------------
    for (auto i = 0; i < m_numberOfRooms; i++)
    {
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_NAME));
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_SETPOINT));
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_WCLOSED));
        addState(oplink::PropertyId::groupPropertyName(i + 1, oplink::PropertyId::P_TEMPERATURE));
    }
}

void HeatingManagerWidgetCtrl::onButtonCmdClicked(QString cmdName)
{
    QString rawFormat("%1;%2;%3;%4"), cmdFormat;

    if (ButtonCmdName::managerOn() == cmdName || ButtonCmdName::managerOff() == cmdName)
    {
        QString val;

        if (ButtonCmdName::managerOn() == cmdName)
        {
            val = oplink::CommandArgs::ON;
        }
        else
        {
            val = oplink::CommandArgs::OFF;
        }

        cmdFormat = rawFormat.arg(oplink::CommandNames::SET,
                                  observableName(),
                                  oplink::PropertyId::P_RUNNING,
                                  val);
        emit execCmd(cmdFormat);
    }
    else if (ButtonCmdName::onDemandMode() == cmdName || ButtonCmdName::plannedMode() == cmdName)
    {
        QString val;

        if (ButtonCmdName::onDemandMode() == cmdName)
        {
            val = oplink::CommandArgs::TRIGGER_MODE_ONDEMAND;
        }
        else
        {
            val = oplink::CommandArgs::TRIGGER_MODE_PLANNED;
        }

        cmdFormat = rawFormat.arg(oplink::CommandNames::SET,
                                  observableName(),
                                  oplink::PropertyId::P_TRIGGER_MODE,
                                  val);
        emit execCmd(cmdFormat);
    }

 /*   else if()
    {

    }*/
}

void HeatingManagerWidgetCtrl::_updateStateValue(const QString &propertyName, const QVariant &value)
{
    MonitoredObservableWidgetView *heatingManagerView{view()};

    if (heatingManagerView)
    {
        if (oplink::PropertyId::P_RUNNING == propertyName)
        {
            heatingManagerView->enableCmdButton(value.toBool(),ButtonCmdName::managerOnOff());
        }
        else if (oplink::PropertyId::P_SETPOINT == propertyName)
        {
            heatingManagerView->setVal(0, value.toDouble()); //idx 0 for setpoint manager value !
        }
        else if (oplink::PropertyId::P_TRIGGER_MODE == propertyName)
        {
            QString val{value.toString()};

            if (oplink::Values::TRIGGER_MODE_ONDEMAND == val)
            {
                heatingManagerView->enableCmdButton(false,ButtonCmdName::triggerPlannedMode());
                heatingManagerView->setImg(m_onDemandImg,oplink::PropertyId::P_DEROGATED);
            }
            else if (oplink::Values::TRIGGER_MODE_PLANNED == val)
            {
                heatingManagerView->enableCmdButton(true,ButtonCmdName::triggerPlannedMode());
                heatingManagerView->setImg(m_plannedImg,oplink::PropertyId::P_DEROGATED);
            }
        }
        else if (oplink::PropertyId::P_DEROGATED == propertyName)
        {
            if (value.toBool())
            {
                heatingManagerView->setImg(m_derogatedImg,oplink::PropertyId::P_DEROGATED);
            }
            else
            {
                heatingManagerView->setImg(m_plannedImg,oplink::PropertyId::P_DEROGATED);
            }
        }
        else
        {
            updateRoomStateValue(propertyName,value);
        }
    }
}

void HeatingManagerWidgetCtrl::extractSchedulerFlagAndNumberOfRooms(QString prefix, QString heatingManagerFullType)
{
    QRegularExpression re("-([am])-(\\d+)");
    QRegularExpressionMatch match = re.match(heatingManagerFullType.remove(prefix));

    if (match.hasMatch()) {
        QString flag = match.captured(1); // scheduler flag a (automatic) > true, m (manual) > false
        QString rooms = match.captured(2); // number of rooms

        m_withScheduler = flag == "a";
        m_numberOfRooms = rooms.toUInt();
    }
}

void HeatingManagerWidgetCtrl::updateRoomStateValue(const QString &propertyName, const QVariant &value)
{
    HeatingManagerWidgetListView *managerView{dynamic_cast<HeatingManagerWidgetListView*>(view())};
    oplink::PropertyName roomProperty;
    quint8 roomNumber;

    if (oplink::PropertyId::isGroupProperty(propertyName,roomNumber,roomProperty))
    {
        if (oplink::PropertyId::P_NAME == roomProperty)
        {
            managerView->setRoomName(roomNumber,value.toString());
        }
        else if (oplink::PropertyId::P_SETPOINT == roomProperty)
        {
            managerView->setRoomSetpoint(roomNumber,value);
        }
        else if (oplink::PropertyId::P_WCLOSED == roomProperty)
        {
            if (true == value.toBool())
            {
                managerView->setRoomImg(roomNumber,m_wClosed,oplink::PropertyId::P_WCLOSED);
            }
            else
            {
                managerView->setRoomImg(roomNumber,m_wOpen,oplink::PropertyId::P_WCLOSED);
            }
        }
        else if (oplink::PropertyId::P_TEMPERATURE == roomProperty)
        {
            managerView->setRoomTemperature(roomNumber,value.toDouble());
        }
    }
}

void HeatingManagerWidgetCtrl::onSetpointChangedFromUi(QVariant val)
{
    QString rawFormat("set;%1;%2;%3"), cmdFormat;

    cmdFormat = rawFormat.arg(observableName(),oplink::PropertyId::P_SETPOINT,val.toString());
    emit execCmd(cmdFormat);
}

void HeatingManagerWidgetCtrl::onRoomSetpointChangedFromUi(int roomNumber, QVariant val)
{
    QString rawFormat("room;%1;%2;%3"), cmdFormat;
    QString roomProperrty{oplink::PropertyId::groupPropertyName(roomNumber,oplink::PropertyId::P_SETPOINT)};

    cmdFormat = rawFormat.arg(observableName(),roomProperrty,val.toString());
    emit execCmd(cmdFormat);
}
