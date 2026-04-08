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

#ifndef HEATING6MWIDGETLISTVIEW_H
#define HEATING6MWIDGETLISTVIEW_H

#include "ui/monitoredobservables/widget/monitoredobservablewidgetlistview.h"

namespace Ui {
class heating6mWidgetListView;
}

class Heating6mWidgetListView : public MonitoredObservableWidgetListView
{
    Q_OBJECT

public:
    explicit Heating6mWidgetListView(QWidget *parent = nullptr);
    ~Heating6mWidgetListView() override;

protected:
    void setTitle(const QString& title) override;
    void setImg(const QPixmap& img, const QString& propertyName) override;
    void setMeasVal(quint32 val) override;
    void setMeasUnit(const QString& unit) override;
    void enableCmdButton(bool enable, const QString& cmdName) override;

private slots:
    void onItemPwmCmd(int index);
    void onPowerCmd();
    void onEnergyCmd();

private:
    Ui::heating6mWidgetListView *ui;
    int                          m_pwmIdx;
};

#endif // HEATING6MWIDGETLISTVIEW_H
