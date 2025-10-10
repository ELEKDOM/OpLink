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


#ifndef OLFCONSOLE_FORWARD_H
#define OLFCONSOLE_FORWARD_H

#include <QSharedPointer>

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{
    enum class PageViewLayout : quint8;

    class OlfLoginController;
    class OlfMonitoredObservablesController;
    class OlfMonitoredObservablesView;
    class OlfLoginView;

    using QspOlfLoginController = QSharedPointer<OlfLoginController>;
    using QspOlfMonitoredObservablesController = QSharedPointer<OlfMonitoredObservablesController>;

    namespace bundle
    {
        class OlfConsole;
    }
    namespace monitoredobservable
    {
        class MonitoredObservableBuilder;
        class PageViewLayoutBuilder;
        class ViewListLayout;

        using QspMonitoredObservableBuilder = QSharedPointer<MonitoredObservableBuilder>;
        using QspPageViewLayoutBuilder = QSharedPointer<PageViewLayoutBuilder>;

        namespace widget
        {
            class MonitoredObservableWidgetCtrl;
            class MonitoredObservableWidgetView;
            class WidgetListView;

            using QspMonitoredObservableWidgetCtrl = QSharedPointer<MonitoredObservableWidgetCtrl>;
        }
    }

}//namespace guiconsole
}//namespace frontend
}//namespace oplink
}//namespace elekdom

#endif // OLFCONSOLE_FORWARD_H
