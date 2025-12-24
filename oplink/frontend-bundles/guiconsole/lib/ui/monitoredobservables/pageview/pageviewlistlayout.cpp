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

#include "pageviewlistlayout.h"
#include "ui_pageviewlistlayout.h"
#include "viewlistlayout.h"

PageViewListLayout::PageViewListLayout(QString toolActionName,QWidget *parent):
    OlfMonitoredObservablesView{toolActionName,parent},
    ui{new Ui::pageViewListLayout}
{
    ui->setupUi(this);
    ui->pageTitle->setText(toolActionName);
}

PageViewListLayout::~PageViewListLayout()
{
    delete ui;
}

void PageViewListLayout::pushUpWidgets()
{
    QList<QWidget*> ListofViewListLayout{findChildren<QWidget*>()};

    for (int j = 0; j < ListofViewListLayout.size(); ++j)
    {
        ViewListLayout *vll{dynamic_cast<ViewListLayout*>(ListofViewListLayout.at(j))};

        if (vll)
        {
            vll->pushUpWidgets();
        }
    }
    ui->widgetListVLayout->addStretch();
}

ViewListLayout *PageViewListLayout::addListView(const QString &listName)
{
    ViewListLayout *ret{new ViewListLayout{listName, this}};

    addWidget(ret);
    return ret;
}

void PageViewListLayout::addWidget(ViewListLayout *w)
{
    ui->widgetListVLayout->addWidget(w);
}
