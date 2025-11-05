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

#include "olconsole.h"
#include "olconsolefactory.h"
#include "bundle/bundlecontext.h"
#include "cmd/cmdprocessor.h"
#include "subscribecmdprocessor.h"

OlConsole::OlConsole():
    m_subscriber{nullptr}
{

}

OlConsole::~OlConsole()
{

}

bool OlConsole::submitOrder(oplink::StrOrder &order)
{
    bool ret{false};
    oplink::ObservableServiceInterface *observableBroker{observableService()};

    ret = observableBroker->submitOrder(order);

    return ret;
}

bool OlConsole::subscribe(oplink::ObservableName name)
{
    bool ret{false};
    oplink::ObservableServiceInterface *observableBroker{observableService()};

    ret = observableBroker->subscribe(name, m_subscriber);

    return ret;
}

bool OlConsole::unsubscribe(oplink::ObservableName name)
{
    bool ret{false};
    oplink::ObservableServiceInterface *observableBroker{observableService()};

    ret = observableBroker->unsubscribe(name, m_subscriber);


    return ret;
}

plugframe::BundleFactory *OlConsole::createFactory()
{
    return new OlConsoleFactory;
}

void OlConsole::buildCommandProcessorSet()
{
    OlConsoleFactory& factory{dynamic_cast<OlConsoleFactory&>(getFactory())};
    QspCmdProcessor cmdProcessor;
    SubscribeCmdProcessor *subscribeProc;

    // specific gac console cmd
    //-------------------------

    // submit command processor
    cmdProcessor = factory.createSubmitCmdProcessor(logChannel(), *this);
    addCmdProcessor(cmdProcessor);

    // subscribe command processor
    cmdProcessor = factory.createSubscribeCmdProcessor(logChannel(), *this);
    addCmdProcessor(cmdProcessor);

    subscribeProc = dynamic_cast<SubscribeCmdProcessor*>(cmdProcessor.get());
    m_subscriber = subscribeProc->observableSubscriber();

    // unsubscribe command processor
    cmdProcessor = factory.createUnsubscribeCmdProcessor(logChannel(), *this);
    addCmdProcessor(cmdProcessor);

    // basic cmd
    //----------
    Console::buildCommandProcessorSet();
}

oplink::ObservableServiceInterface *OlConsole::observableService()
{
     return bundleContext()->getService<oplink::ObservableServiceInterface>(oplink::ObservableServiceInterface::serviceName());
}


