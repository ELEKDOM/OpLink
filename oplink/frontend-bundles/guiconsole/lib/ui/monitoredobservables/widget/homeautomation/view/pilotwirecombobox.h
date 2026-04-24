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

#ifndef PILOTWIRECOMBOBOX_H
#define PILOTWIRECOMBOBOX_H

#include <QWidget>
#include <QIcon>
#include "pilotwire4widget.h"

namespace Ui {
class pilotWireComboBox;
}

class PilotWireComboBox : public QWidget
{
    Q_OBJECT

private:
    enum class LockerState{Locked, Unlocked};

public:
    PilotWireComboBox(bool pw6 = false, QWidget *parent = nullptr);
    ~PilotWireComboBox() override;

public:
    void setValue(QString s);

signals:
    void valueChanged(QString v);

private slots:
    void onLockerClicked(bool checked);
    void onSelectedOrderChanged(QString ord);

private:
    void lockInput();
    void unlockInput();
    void validateInput();

private:
    Ui::pilotWireComboBox *ui;
    PilotWire4Widget      *m_pwInput;
    LockerState            m_lockerState;
    QIcon                  m_lockedIcon;
    QIcon                  m_unlockedIcon;
    QString                m_selectedOrder;
};

#endif // PILOTWIRECOMBOBOX_H
