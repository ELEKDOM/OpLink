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

#ifndef D201SETOUTPUT_H
#define D201SETOUTPUT_H

#include "d201commandprocessor.h"

// EnOcean Command 0x01 : Actuator Set Output
class D201SetOutput : public D201CommandProcessor
{
public:
    D201SetOutput(const oplink::QspDevice& device);
    ~D201SetOutput() override;

protected:
    bool completePacket(oplink::QspCommand order) override;

private:
    void setOutput(quint8 channel, quint8 val);
};

#endif // D201SETOUTPUT_H
