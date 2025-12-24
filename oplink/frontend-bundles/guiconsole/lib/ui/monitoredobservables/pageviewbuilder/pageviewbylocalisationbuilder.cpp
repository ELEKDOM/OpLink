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

#include "pageviewbylocalisationbuilder.h"
#include "monitoredobservablebuilder.h"
#include "ui/olfmonitoredobservablescontroller.h"
#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"

PageViewByLocalisationBuilder::PageViewByLocalisationBuilder()
{}

PageViewByLocalisationBuilder::~PageViewByLocalisationBuilder()
{

}

QString PageViewByLocalisationBuilder::getViewName(QspMonitoredObservableWidgetCtrl &widgetCtrl)
{
    return widgetCtrl->observableLocalisation();
}

QString PageViewByLocalisationBuilder::getListLayoutName(QspMonitoredObservableWidgetCtrl &widgetCtrl)
{
    return builder()->getFamilyName(widgetCtrl->observableType());
}

quint8 PageViewByLocalisationBuilder::getLayoutType()
{
    return static_cast<quint8>(PageViewLayout::LocalisationListLayout);
}
