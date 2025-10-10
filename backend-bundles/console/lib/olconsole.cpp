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
#include "observable/observable/observablesubscriber.h"

using namespace elekdom::oplink::console::bundle;
using namespace elekdom::oplink::engine::service;
using namespace elekdom::plugframe::console::bundle;

OlConsole::OlConsole():
    m_subscriber{nullptr}
{

}

OlConsole::~OlConsole()
{

}

bool OlConsole::submitOrder(StrOrder &order)
{
    bool ret{false};
    engine::service::ObservableServiceInterface *observableBroker{observableService()};

    ret = observableBroker->submitOrder(order);

    return ret;
}

bool OlConsole::subscribe(core::observable::ObservableName name)
{
    bool ret{false};
    engine::service::ObservableServiceInterface *observableBroker{observableService()};

    ret = observableBroker->subscribe(name, m_subscriber);

    return ret;
}

bool OlConsole::unsubscribe(core::observable::ObservableName name)
{
    bool ret{false};
    engine::service::ObservableServiceInterface *observableBroker{observableService()};

    ret = observableBroker->unsubscribe(name, m_subscriber);


    return ret;
}

elekdom::plugframe::core::bundle::BundleFactory *OlConsole::createFactory()
{
    return new factory::OlConsoleFactory;
}

void OlConsole::buildCommandProcessorSet()
{
    factory::OlConsoleFactory& factory{dynamic_cast<factory::OlConsoleFactory&>(getFactory())};
    QspCmdProcessor cmdProcessor;

    // specific gac console cmd
    //-------------------------

    // submit command processor
    cmdProcessor = factory.createSubmitCmdProcessor(logChannel(), *this);
    addCmdProcessor(cmdProcessor);

    // subscribe command processor
    cmdProcessor = factory.createSubscribeCmdProcessor(logChannel(), *this);
    addCmdProcessor(cmdProcessor);
    m_subscriber = dynamic_cast<core::observable::ObservableSubscriber*>(cmdProcessor.get());

    // unsubscribe command processor
    cmdProcessor = factory.createUnsubscribeCmdProcessor(logChannel(), *this);
    addCmdProcessor(cmdProcessor);

    // basic cmd
    //----------
    Console::buildCommandProcessorSet();
}

ObservableServiceInterface *OlConsole::observableService()
{
     return bundleContext()->getService<elekdom::oplink::engine::service::ObservableServiceInterface>(elekdom::oplink::engine::service::ObservableServiceInterface::serviceName());
}


