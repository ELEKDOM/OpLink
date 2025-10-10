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


#include "monitoredobservablewidgetview.h"

using namespace elekdom::oplink::frontend::guiconsole::monitoredobservable::widget;

MonitoredObservableWidgetView::MonitoredObservableWidgetView(QWidget *parent):
    QWidget{parent}
{}

MonitoredObservableWidgetView::~MonitoredObservableWidgetView()
{

}

void MonitoredObservableWidgetView::setTitle(const QString &title)
{
    Q_UNUSED(title)
}

void MonitoredObservableWidgetView::setImg(const QPixmap &img, const QString &propertyName)
{
    Q_UNUSED(img)
    Q_UNUSED(propertyName)
}

void MonitoredObservableWidgetView::enableCmdButton(bool enable, const QString &cmdName)
{
    Q_UNUSED(enable)
    Q_UNUSED(cmdName)
}

void MonitoredObservableWidgetView::setMeasVal(quint32 val)
{
    Q_UNUSED(val)
}

void MonitoredObservableWidgetView::setMeasUnit(const QString &unit)
{
    Q_UNUSED(unit)
}

void MonitoredObservableWidgetView::setVal(quint8 idx, double val)
{
    Q_UNUSED(idx)
    Q_UNUSED(val)
}

