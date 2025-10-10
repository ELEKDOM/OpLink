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
#include "ui/monitoredobservables/widget/view/widgetlistview.h"
#include "ui/monitoredobservables/pageview/viewlistlayout.h"

using namespace elekdom::oplink::frontend::guiconsole::monitoredobservable;

PageViewListLayoutBuilder::PageViewListLayoutBuilder() {}

PageViewListLayoutBuilder::~PageViewListLayoutBuilder()
{

}

void PageViewListLayoutBuilder::assignWidgetView(OlfMonitoredObservablesController &controller,
                                                 widget::QspMonitoredObservableWidgetCtrl &widgetCtrl)
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
    widget::MonitoredObservableWidgetView *wv{widgetCtrl->createView(getLayoutType())};
    widget::WidgetListView *widgetView{dynamic_cast<widget::WidgetListView*>(wv)};

    if (widgetView)
    {
        listLayoutView->addWidget(widgetView);
    }
}

elekdom::oplink::frontend::guiconsole::OlfMonitoredObservablesView *PageViewListLayoutBuilder::createMonitoredObservablesView(QString pageName)
{
    return new PageViewListLayout(pageName);
}
