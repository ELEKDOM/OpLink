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

#include "commandprocessor.h"
#include "observable/observablelogchannel.h"
#include "command/command.h"
#include "observable/observable/observable.h"

oplink::CommandProcessor::CommandProcessor(oplink::Observable& observable,
                                           const oplink::CommandName& cmdName):
    plugframe::Loggable{s_ObservableLogChannel},
    m_observable{observable},
    m_cmdName{cmdName}
{

}

oplink::CommandProcessor::~CommandProcessor()
{

}

bool oplink::CommandProcessor::acceptCmd(oplink::QspCommand order)
{
    bool ret{checkTarget(order)};

    if (ret)
    {
        process(order);
    }

    return ret;
}

bool oplink::CommandProcessor::checkTarget(oplink::QspCommand &order)
{
    bool ret;

    ret = (order->name() == m_cmdName) && (order->observable() == m_observable.name());

    return ret;
}
