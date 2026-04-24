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

#ifndef Command_H
#define Command_H

#include <QString>
#include <QVariant>
#include <QSharedPointer>
#include "olcore-backend-lib_export.h"
#include "command/command-names.h"
#include "observable/observablenames.h"
#include "observable/propertyid.h"

namespace oplink
{
/////////////////////////////////////
/// \brief The GacCommand class
/// \details Command format : command <observable name> [<property name>] [<par1> <par2> ... <parn>]
///          a command is a vector string where:
///             index 0 command to proccess by the observable
///             index 1 name of the observable on which the command is applied
///             index 2 observable's property name (could be empty)
///             index 3 ... command's pars (could be empty)
class OLCORE_BACKEND_LIB_EXPORT Command
{
protected:
    static const int COMMAND_NAME_IDX;
    static const int TARGET_OBSERVABLE_IDX;
    static const int TARGET_PROPERTY_IDX;
    static const int TARGET_VALUE_IDX;

public:
    Command(StrOrder cmdStr);
    virtual ~Command();

public:
    const CommandName name();
    const ObservableName observable();
    const PropertyName property();
    QVariant value();
    void replaceTarget(const ObservableName& oname,const PropertyName& pname);

private:
    QStringList   m_args;
};
using QspCommand = QSharedPointer<Command>;
}//namespace oplink
#endif // Command_H
