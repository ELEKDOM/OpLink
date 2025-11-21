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

#ifndef ACTUATOROUTPUTSBINDING_H
#define ACTUATOROUTPUTSBINDING_H

#include <QVector>
#include <QSharedPointer>
#include "olcore-backend-lib_export.h"
#include "actuatoroutput.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ActuatorOutputsBinding
{
public:
    ActuatorOutputsBinding();
    ~ActuatorOutputsBinding();

public:
    void append(const ActuatorOutput& newOutput);
    const ActuatorOutput& at(int i) const;
    qsizetype size() const;

private:
    QVector<ActuatorOutput> m_outputs;
};
}//namespace oplink
#endif // ACTUATOROUTPUTSBINDING_H
