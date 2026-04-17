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

#ifndef TEMPDOUBLESPINBOX_H
#define TEMPDOUBLESPINBOX_H

#include <QWidget>
#include <QIcon>

namespace Ui {
class tempDoubleSpinBox;
}

class TempDoubleSpinBox : public QWidget
{
    Q_OBJECT
private:
    enum class LockerState{Locked, Unlocked};

public:
    explicit TempDoubleSpinBox(QWidget *parent = nullptr);
    ~TempDoubleSpinBox() override;

public:
    void setValue(double d);

signals:
    void valueChanged(double v);

private slots:
    void onLockerClicked(bool checked);

private:
    void lockInput();
    void unlockInput();
    void validateInput();

private:
    Ui::tempDoubleSpinBox *ui;
    LockerState m_lockerState;
    QIcon   m_lockedIcon;
    QIcon   m_unlockedIcon;
};

#endif // TEMPDOUBLESPINBOX_H
