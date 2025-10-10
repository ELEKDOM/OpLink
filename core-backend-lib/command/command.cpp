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


#include "command.h"

using namespace elekdom::oplink::core::command;
using namespace elekdom::oplink::core;

const int Command::COMMAND_NAME_IDX = 0;
const int Command::TARGET_OBSERVABLE_IDX = 1;
const int Command::TARGET_PROPERTY_IDX = 2;
const int Command::TARGET_VALUE_IDX = 3;

Command::Command(StrOrder cmdStr)
{
    StrOrder order{cmdStr.toLower()};
    m_args = order.split(' ');
}

Command::~Command()
{

}

const CommandName Command::name()
{
    CommandName ret;

    if (m_args.size() > COMMAND_NAME_IDX)
    {
        ret = m_args.at(COMMAND_NAME_IDX);
    }
    return ret;
}

const observable::ObservableName Command::observable()
{
    observable::ObservableName ret;

    if (m_args.size() > TARGET_OBSERVABLE_IDX)
    {
        ret = m_args.at(TARGET_OBSERVABLE_IDX);
    }
    return ret;
}

const observable::PropertyName Command::property()
{
    observable::PropertyName ret;

    if (m_args.size() > TARGET_PROPERTY_IDX)
    {
        ret = m_args.at(TARGET_PROPERTY_IDX);
    }
    return ret;
}

QVariant Command::value()
{
    QVariant ret;

    if (m_args.size() > TARGET_VALUE_IDX)
    {
        ret = QVariant(m_args.at(TARGET_VALUE_IDX));
    }
    return ret;
}

void Command::replaceTarget(const observable::ObservableName &oname, const observable::PropertyName &pname)
{
    m_args[TARGET_OBSERVABLE_IDX] = oname;
    m_args[TARGET_PROPERTY_IDX] = pname;
}
