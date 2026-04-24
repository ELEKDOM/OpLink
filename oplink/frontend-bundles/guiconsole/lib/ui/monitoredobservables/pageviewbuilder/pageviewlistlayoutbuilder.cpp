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

#include "pageviewlistlayoutbuilder.h"
#include "ui/olfmonitoredobservablescontroller.h"
#include "ui/monitoredobservables/pageview/pageviewlistlayout.h"
#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"
#include "ui/monitoredobservables/widget/monitoredobservablewidgetlistview.h"
#include "ui/monitoredobservables/pageview/viewlistlayout.h"

PageViewListLayoutBuilder::PageViewListLayoutBuilder() {}

PageViewListLayoutBuilder::~PageViewListLayoutBuilder()
{

}

void PageViewListLayoutBuilder::assignWidgetView(OlfMonitoredObservablesController &controller,
                                                 QspMonitoredObservableWidgetCtrl &widgetCtrl)
{
    QString viewName,listLayoutTitle;
    OlfMonitoredObservablesView *pageView;

    // Need a new PageView ?
    viewName = getViewName(widgetCtrl);
    pageView = controller.viewByName(viewName);
    if (!pageView)
    {
        pageView = createMonitoredObservablesView(viewName);
        controller.addMonitoredObservablesView(pageView);
    }

    // Need a new ListView into the page ?
    listLayoutTitle = getListLayoutName(widgetCtrl);
    ViewListLayout *listLayoutView{dynamic_cast<ViewListLayout*>(pageView->findChild<QWidget*>(listLayoutTitle))};
    if (!listLayoutView)
    {
        listLayoutView = pageView->addListView(listLayoutTitle);
    }

    // Add a new widgetview into the list
    MonitoredObservableWidgetView *wv{widgetCtrl->createView(getLayoutType())};
    MonitoredObservableWidgetListView *widgetView{dynamic_cast<MonitoredObservableWidgetListView*>(wv)};

    if (widgetView)
    {
        listLayoutView->addWidget(widgetView);
    }
}

OlfMonitoredObservablesView *PageViewListLayoutBuilder::createMonitoredObservablesView(QString pageName)
{
    return new PageViewListLayout(pageName);
}
