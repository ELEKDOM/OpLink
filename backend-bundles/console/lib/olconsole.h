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


#ifndef OLCONSOLE_H
#define OLCONSOLE_H

#include "console.h"
#include "command/command-names.h"
#include "observable/observablenames.h"
#include "service-int/observableserviceinterface.h"

using namespace elekdom::oplink::core::command;

namespace elekdom
{
namespace oplink
{
namespace console
{
namespace bundle
{

class OlConsole: public elekdom::plugframe::console::bundle::Console
{

public:
    OlConsole();
    ~OlConsole() override;

public:
    bool submitOrder(StrOrder& order);
    bool subscribe(core::observable::ObservableName name);
    bool unsubscribe(core::observable::ObservableName name);

protected:
    plugframe::core::bundle::BundleFactory* createFactory() override;
    void buildCommandProcessorSet() override;

protected:
    engine::service::ObservableServiceInterface *observableService();

private:
    core::observable::ObservableSubscriber *m_subscriber;
};

}//namespace bundle
}//namespace console
}//namespace oplink
}//namespace elekdom

#endif // OLCONSOLE_H
