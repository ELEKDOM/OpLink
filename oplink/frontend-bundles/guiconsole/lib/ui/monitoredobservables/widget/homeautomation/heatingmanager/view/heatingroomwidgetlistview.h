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

#ifndef HEATINGROOMWIDGETLISTVIEW_H
#define HEATINGROOMWIDGETLISTVIEW_H

#include <QWidget>

namespace Ui {
class heatingRoomWidgetListView;
}

class HeatingRoomWidgetListView : public QWidget
{
    Q_OBJECT

public:
    explicit HeatingRoomWidgetListView(int roomNumber, QWidget *parent = nullptr);
    ~HeatingRoomWidgetListView() override;

public:
    virtual void setpointValue(const QVariant& val) = 0;
    void setRoomName(const QString& roomName);
    void setImg(const QPixmap& img, const QString& propertyName);
    void setTemperature(double value);

protected:
    void addSetpointInputWidget(QWidget *inputWidget);

protected:
    int roomNumber() {return m_roomNumber;}

signals:
    void setpointChangedFromUi(int roomNumber, QVariant val);

private:
    int                            m_roomNumber;
    Ui::heatingRoomWidgetListView *ui;

};

#endif // HEATINGROOMWIDGETLISTVIEW_H
