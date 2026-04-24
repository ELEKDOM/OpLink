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

#include "pilotwirecombobox.h"
#include "ui_pilotwirecombobox.h"
#include "pilotwire6widget.h"

PilotWireComboBox::PilotWireComboBox(bool pw6, QWidget *parent):
    QWidget{parent},
    ui{new Ui::pilotWireComboBox},
    m_lockedIcon{QIcon(":/img/hm_lock.png")},
    m_unlockedIcon{QIcon(":/img/hm_unlock.png")}
{
    ui->setupUi(this);

    if (pw6)
    {
        m_pwInput = new PilotWire6Widget;
    }
    else
    {
        m_pwInput = new PilotWire4Widget;
    }
    ui->pilotWireLayout->addWidget(m_pwInput);

    lockInput();
    connect(ui->lockerBp,SIGNAL(clicked(bool)),SLOT(onLockerClicked(bool)));
    connect(m_pwInput,SIGNAL(pilotWireOrderSelected(QString)),SLOT(onSelectedOrderChanged(QString)));
}

PilotWireComboBox::~PilotWireComboBox()
{
}

void PilotWireComboBox::setValue(QString s)
{
    m_pwInput->selectItem(s);
}

void PilotWireComboBox::onLockerClicked(bool checked)
{
    switch(m_lockerState)
    {
    case LockerState::Locked:
        unlockInput();
        break;

    case LockerState::Unlocked:
        validateInput();
        break;
    }
}

void PilotWireComboBox::onSelectedOrderChanged(QString ord)
{
    m_selectedOrder = ord;
}

void PilotWireComboBox::lockInput()
{
    m_lockerState = LockerState::Locked;
    ui->lockerBp->setIcon(m_lockedIcon);
    m_pwInput->setEnabled(false);
}

void PilotWireComboBox::unlockInput()
{
    m_lockerState = LockerState::Unlocked;
    ui->lockerBp->setIcon(m_unlockedIcon);
    m_pwInput->setEnabled(true);
}

void PilotWireComboBox::validateInput()
{
    lockInput();
    emit valueChanged(m_selectedOrder);
}
