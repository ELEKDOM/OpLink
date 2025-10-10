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


#ifndef OLFCONSOLEVIEW_H
#define OLFCONSOLEVIEW_H

#include "gui/guipageview.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{

class OlfConsoleView : public plugframe::core::gui::GuiPageView
{
    Q_OBJECT

public:
    explicit OlfConsoleView(QString toolActionName,QWidget *parent = nullptr);
    ~OlfConsoleView() override;
};

} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFCONSOLEVIEW_H
