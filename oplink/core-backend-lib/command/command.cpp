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

const int oplink::Command::COMMAND_NAME_IDX = 0;
const int oplink::Command::TARGET_OBSERVABLE_IDX = 1;
const int oplink::Command::TARGET_PROPERTY_IDX = 2;
const int oplink::Command::TARGET_VALUE_IDX = 3;

oplink::Command::Command(StrOrder cmdStr)
{
    oplink::StrOrder order{cmdStr.toLower()};
    m_args = order.split(' ');
}

oplink::Command::~Command()
{

}

const oplink::CommandName oplink::Command::name()
{
    oplink::CommandName ret;

    if (m_args.size() > COMMAND_NAME_IDX)
    {
        ret = m_args.at(COMMAND_NAME_IDX);
    }
    return ret;
}

const oplink::ObservableName oplink::Command::observable()
{
    oplink::ObservableName ret;

    if (m_args.size() > TARGET_OBSERVABLE_IDX)
    {
        ret = m_args.at(TARGET_OBSERVABLE_IDX);
    }
    return ret;
}

const oplink::PropertyName oplink::Command::property()
{
    oplink::PropertyName ret;

    if (m_args.size() > TARGET_PROPERTY_IDX)
    {
        ret = m_args.at(TARGET_PROPERTY_IDX);
    }
    return ret;
}

QVariant oplink::Command::value()
{
    QVariant ret;

    if (m_args.size() > TARGET_VALUE_IDX)
    {
        ret = QVariant(m_args.at(TARGET_VALUE_IDX));
    }
    return ret;
}

void oplink::Command::replaceTarget(const oplink::ObservableName &oname,const oplink::PropertyName &pname)
{
    m_args[TARGET_OBSERVABLE_IDX] = oname;
    m_args[TARGET_PROPERTY_IDX] = pname;
}
