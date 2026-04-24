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

#ifndef HEATINGROOMPWTWIDGETLISTVIEW_H
#define HEATINGROOMPWTWIDGETLISTVIEW_H

#include "heatingroomwidgetlistview.h"
#include "ui/monitoredobservables/widget/homeautomation/view/tempdoublespinbox.h"

class HeatingRoomPwtWidgetListView : public HeatingRoomWidgetListView
{
    Q_OBJECT

public:
    explicit HeatingRoomPwtWidgetListView(int roomNumber, QWidget *parent = nullptr);
    ~HeatingRoomPwtWidgetListView() override;

protected:
    void setpointValue(const QVariant& val) override;

private slots:
    void onSetpointValueChanged(double d);

private:
    TempDoubleSpinBox *m_setpointInputWidget;
};

#endif // HEATINGROOMPWTWIDGETLISTVIEW_H
