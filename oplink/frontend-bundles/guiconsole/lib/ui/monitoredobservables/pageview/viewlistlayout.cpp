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

#include "viewlistlayout.h"
#include "ui_viewlistlayout.h"
#include "ui/monitoredobservables/widget/view/widgetlistview.h"

ViewListLayout::ViewListLayout(const QString title, QWidget *parent):
    QWidget(parent)
    , ui(new Ui::viewListLayout)
    , m_expanded{true}
    , m_plusIcon{QIcon(":/img/plus.png")}
    , m_minusIcon{QIcon(":/img/minus.png")}
{
    setObjectName(title);
    ui->setupUi(this);
    ui->title->setText(title);
    ui->expandBp->setIcon(m_minusIcon);
    connect(ui->expandBp, SIGNAL(pressed()), SLOT(onExpand()));
}

ViewListLayout::~ViewListLayout()
{

}

void ViewListLayout::addWidget(WidgetListView *widget)
{
    ui->verticalLayout_3->addWidget(widget);
}

void ViewListLayout::pushUpWidgets()
{
    ui->verticalLayout_3->addStretch();
}

void ViewListLayout::onExpand()
{
    if (m_expanded)
    {
        ui->body->hide();
        m_expanded = false;
        ui->expandBp->setIcon(m_plusIcon);
    }
    else
    {
        ui->body->show();
        m_expanded = true;
        ui->expandBp->setIcon(m_minusIcon);
    }
}
