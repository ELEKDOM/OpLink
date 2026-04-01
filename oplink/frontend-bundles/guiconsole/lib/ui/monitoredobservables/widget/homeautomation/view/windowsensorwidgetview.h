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

#ifndef WINDOWSENSORWIDGETVIEW_H
#define WINDOWSENSORWIDGETVIEW_H

#include "ui/monitoredobservables/widget/monitoredobservablewidgetlistview.h"

namespace Ui {
class windowSensorWidgetView;
}

class WindowSensorWidgetView : public MonitoredObservableWidgetListView
{
    Q_OBJECT

public:
    WindowSensorWidgetView(QWidget *parent = nullptr);
    ~WindowSensorWidgetView() override;

protected:
    void setTitle(const QString& title) override;
    void setImg(const QPixmap& img, const QString& propertyName) override;

private:
    Ui::windowSensorWidgetView *ui;
};

#endif // WINDOWSENSORWIDGETVIEW_H
