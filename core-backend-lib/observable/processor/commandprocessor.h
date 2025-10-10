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

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "logger/loggable.h"
#include "command/command-names.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class OLCORE_BACKEND_LIB_EXPORT CommandProcessor : public plugframe::core::logger::Loggable
{
public:
    CommandProcessor(const Observable& observable,
                        const command::CommandName& cmdName);
    ~CommandProcessor() override;

public:
    const Observable& observable() {return m_observable;}
    command::CommandName cmdName() {return m_cmdName;}

public:
    bool acceptCmd(QSharedPointer<command::Command> order);

protected:
    bool checkTarget(command::QspCommand& order);
    virtual void process(command::QspCommand order) = 0;

private:
    const Observable&    m_observable;
    command::CommandName m_cmdName;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // COMMANDPROCESSOR_H
