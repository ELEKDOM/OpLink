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

#ifndef D201CMD8FORMAT_H
#define D201CMD8FORMAT_H

#include <QSharedPointer>
#include "d201commandformat.h"

// EnOcean Command 0x08 : Actuator Set Pilot Wire Mode
class D201Cmd8Format : public D201CommandFormat
{
public:
    D201Cmd8Format();
    ~D201Cmd8Format() override;

public:
    void setMode(quint8 mode);
};
using QspD201Cmd8Format = QSharedPointer<D201Cmd8Format>;
#endif // D201CMD8FORMAT_H
