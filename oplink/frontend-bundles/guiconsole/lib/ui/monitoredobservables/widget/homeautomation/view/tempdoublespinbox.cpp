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

#include "tempdoublespinbox.h"
#include "ui_tempdoublespinbox.h"

TempDoubleSpinBox::TempDoubleSpinBox(QWidget *parent):
    QWidget{parent},
    ui{new Ui::tempDoubleSpinBox},
    m_lockedIcon{QIcon(":/img/hm_lock.png")},
    m_unlockedIcon{QIcon(":/img/hm_unlock.png")}
{
    ui->setupUi(this);
    lockInput();

    connect(ui->lockerBp,SIGNAL(clicked(bool)),SLOT(onLockerClicked(bool)));
}

TempDoubleSpinBox::~TempDoubleSpinBox()
{

}

void TempDoubleSpinBox::setValue(double d)
{
    ui->tempSpinBox->setValue(d);
}

void TempDoubleSpinBox::onLockerClicked(bool checked)
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

void TempDoubleSpinBox::lockInput()
{
    m_lockerState = LockerState::Locked;
    ui->lockerBp->setIcon(m_lockedIcon);
    ui->tempSpinBox->setReadOnly(true);
}

void TempDoubleSpinBox::unlockInput()
{
    m_lockerState = LockerState::Unlocked;
    ui->lockerBp->setIcon(m_unlockedIcon);
    ui->tempSpinBox->setReadOnly(false);
}

void TempDoubleSpinBox::validateInput()
{
    lockInput();
    emit valueChanged(ui->tempSpinBox->value());
}
