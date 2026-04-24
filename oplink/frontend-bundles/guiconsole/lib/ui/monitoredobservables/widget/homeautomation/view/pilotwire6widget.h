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

#ifndef PILOTWIRE6WIDGET_H
#define PILOTWIRE6WIDGET_H

#include "pilotwire4widget.h"

class PilotWire6Widget : public PilotWire4Widget
{
    Q_OBJECT

public:
    explicit PilotWire6Widget(QWidget *parent = nullptr);
    ~PilotWire6Widget() override;
};

#endif // PILOTWIRE6WIDGET_H
