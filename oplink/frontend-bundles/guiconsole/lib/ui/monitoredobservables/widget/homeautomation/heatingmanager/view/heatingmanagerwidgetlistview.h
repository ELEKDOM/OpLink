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

#ifndef HEATINGMANAGERWIDGETLISTVIEW_H
#define HEATINGMANAGERWIDGETLISTVIEW_H

#include <QVector>
#include <QVBoxLayout>
#include "ui/monitoredobservables/widget/monitoredobservablewidgetlistview.h"

namespace Ui {
class heatingManagerWidgetListView;
}

class HeatingRoomWidgetListView;
class HeatingManagerWidgetListView : public MonitoredObservableWidgetListView
{
    Q_OBJECT

public:
    HeatingManagerWidgetListView(bool withScheduler,QWidget *parent = nullptr);
    ~HeatingManagerWidgetListView() override;

public:
    virtual void setSetpointVal(const QVariant& value) = 0;
    virtual void setRoomName(quint8 roomNumber,const QString& roomName);
    virtual void setRoomSetpoint(quint8 roomNumber,const QVariant& value);
    virtual void setRoomImg(quint8 roomNumber,const QPixmap& img, const QString& propertyName);
    virtual void setRoomTemperature(quint8 roomNumber,double value);

protected:
    void setTitle(const QString& title) override;
    void enableCmdButton(bool enable, const QString& cmdName) override;
    void setImg(const QPixmap& img, const QString& propertyName) override;

protected:
    void addSetpointInputWidget(QWidget *inputWidget);
    QWidget *heatingManagerWidgetContent();
    QVBoxLayout *contentVerticalLayout();

private slots:
    void onOnOffSliderValueChanged(int value);
    void onPlannedToggled(bool checked);
    void onOnDemandToggled(bool checked);

private:
    void enableManagerView(bool enable);
    void enableRoomsView(bool enable);

signals:
    void setpointChangedFromUi(QVariant val);
    void roomSetpointChangedFromUi(int roomNumber,QVariant val);

protected:
    QVector<HeatingRoomWidgetListView*> ui_rooms;

private:
    Ui::heatingManagerWidgetListView   *ui;
};

#endif // HEATINGMANAGERWIDGETLISTVIEW_H
