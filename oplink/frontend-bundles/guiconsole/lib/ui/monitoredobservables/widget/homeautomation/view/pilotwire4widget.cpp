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

#include "pilotwire4widget.h"
#include "ui/monitoredobservables/widget/buttoncmdname.h"

PilotWire4Widget::PilotWire4Widget(QWidget *parent)
    : QComboBox{parent},
    m_selectedIdx{-1}
{
    addItem(tr("confort"), ButtonCmdName::comfort());
    addItem(tr("eco"), ButtonCmdName::eco());
    addItem(tr("hors gel"), ButtonCmdName::nofrost());
    addItem(tr("arrêt"), ButtonCmdName::off());

    connect(this, SIGNAL(activated(int)), SLOT(onItemSelected(int)));
}

PilotWire4Widget::~PilotWire4Widget()
{

}

void PilotWire4Widget::selectItem(const QString &pilotWireOrder)
{
    m_selectedIdx = findData(pilotWireOrder);
    if (-1 != m_selectedIdx)
    {
        setCurrentIndex(m_selectedIdx);
    }
}

void PilotWire4Widget::onItemSelected(int index)
{
    if (index != m_selectedIdx)
    {
        QVariant cmdArg{itemData(index)};

        emit pilotWireOrderSelected(cmdArg.toString());
    }
}
