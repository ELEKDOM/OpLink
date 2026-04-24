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

#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <QSharedPointer>
#include "logger/loggable.h"
#include "command/command-names.h"
#include "command/command.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT CommandProcessor : public plugframe::Loggable
{
public:
    CommandProcessor(Observable& observable,
                     const CommandName& cmdName);
    ~CommandProcessor() override;

public:
    Observable& observable() {return m_observable;}
    CommandName cmdName() {return m_cmdName;}

public:
    bool acceptCmd(QspCommand order);

protected:
    bool checkTarget(QspCommand& order);
    virtual void process(QspCommand order) = 0;

private:
    Observable& m_observable;
    CommandName m_cmdName;
};
using QspCommandProcessor = QSharedPointer<CommandProcessor>;
}//namespace oplink
#endif // COMMANDPROCESSOR_H
