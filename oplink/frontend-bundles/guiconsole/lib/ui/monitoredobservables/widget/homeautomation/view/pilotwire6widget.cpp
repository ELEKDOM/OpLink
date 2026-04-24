// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#include "pilotwire6widget.h"
#include "ui/monitoredobservables/widget/buttoncmdname.h"

PilotWire6Widget::PilotWire6Widget(QWidget *parent)
{
    insertItem(1, tr("confort - 1"), ButtonCmdName::comfort1());
    insertItem(2, tr("confort - 2"), ButtonCmdName::comfort2());
}

PilotWire6Widget::~PilotWire6Widget()
{

}
