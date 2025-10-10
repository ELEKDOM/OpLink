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


#ifndef VIEWLISTLAYOUT_H
#define VIEWLISTLAYOUT_H

#include <QWidget>
#include <QIcon>
#include "olfconsole_forward.h"

namespace Ui {
class viewListLayout;
}

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{
namespace monitoredobservable
{

class ViewListLayout  : public QWidget
{
    Q_OBJECT

public:
    explicit ViewListLayout(const QString title, QWidget *parent = nullptr);
    ~ViewListLayout() override;

public:
    void addWidget(widget::WidgetListView* widget);
    void pushUpWidgets();

private slots:
    void onExpand();

private:
    Ui::viewListLayout *ui;
    bool    m_expanded;
    QIcon   m_plusIcon;
    QIcon   m_minusIcon;
};

} //namespace monitoredobservable
} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // VIEWLISTLAYOUT_H
