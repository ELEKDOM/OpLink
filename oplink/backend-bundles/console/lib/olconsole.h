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

class OlConsole: public Console
{

public:
    OlConsole();
    ~OlConsole() override;

public:
    bool submitOrder(oplink::StrOrder& order);
    bool subscribe(oplink::ObservableName name);
    bool unsubscribe(oplink::ObservableName name);

protected:
    plugframe::BundleFactory* createFactory() override;
    void buildCommandProcessorSet() override;

protected:
    oplink::ObservableServiceInterface *observableService();

private:
    oplink::ObservableSubscriber *m_subscriber;
};
#endif // OLCONSOLE_H
