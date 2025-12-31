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

#ifndef PAGEVIEWLISTLAYOUTBUILDER_H
#define PAGEVIEWLISTLAYOUTBUILDER_H

#include "pageviewlayoutbuilder.h"

class PageViewListLayoutBuilder : public PageViewLayoutBuilder
{
public:
    PageViewListLayoutBuilder();
    ~PageViewListLayoutBuilder() override;

protected:
    void assignWidgetView(OlfMonitoredObservablesController& controller,
                          QspMonitoredObservableWidgetCtrl& widgetCtrl) override;
    virtual QString getViewName(QspMonitoredObservableWidgetCtrl& widgetCtrl) = 0;
    virtual QString getListLayoutName(QspMonitoredObservableWidgetCtrl& widgetCtrl) = 0;
    virtual quint8 getLayoutType() = 0;
    virtual OlfMonitoredObservablesView *createMonitoredObservablesView(QString pageName);

};

#endif // PAGEVIEWLISTLAYOUTBUILDER_H
