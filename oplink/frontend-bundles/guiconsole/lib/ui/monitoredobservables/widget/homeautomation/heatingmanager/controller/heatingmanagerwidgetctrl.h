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

#ifndef HEATINGMANAGERWIDGETCTRL_H
#define HEATINGMANAGERWIDGETCTRL_H

#include <QPixmap>
#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"

class HeatingManagerWidgetCtrl : public MonitoredObservableWidgetCtrl
{
    Q_OBJECT

public:
    HeatingManagerWidgetCtrl(QString observableName,
                             QString observableTitle,
                             QString observableType,
                             QString observableLocalisation);
    ~HeatingManagerWidgetCtrl() override;

protected:
    void extendedConnect() override;

protected:
    void createStates() override;
    void onButtonCmdClicked(QString cmdName) override;
    void _updateStateValue(const QString &propertyName,
                           const QVariant &value) override;

protected:
    void extractSchedulerFlagAndNumberOfRooms(QString prefix, QString heatingManagerFullType);
    bool withScheduler() {return m_withScheduler;}
    int numberOfRooms() {return m_numberOfRooms;}

protected:
    void updateSetpointValue(const QVariant &value);
    virtual void updateRoomStateValue(const QString &propertyName,
                                      const QVariant &value);
private slots:
    void onSetpointChangedFromUi(QVariant val);
    void onRoomSetpointChangedFromUi(int roomNumber,QVariant val);

private:
    bool m_withScheduler;
    int  m_numberOfRooms;
    QPixmap m_derogatedImg;
    QPixmap m_plannedImg;
    QPixmap m_onDemandImg;
    QPixmap m_wOpen;
    QPixmap m_wClosed;
};

#endif // HEATINGMANAGERWIDGETCTRL_H
