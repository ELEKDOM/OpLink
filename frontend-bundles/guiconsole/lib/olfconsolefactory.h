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


#ifndef OLFCONSOLEFACTORY_H
#define OLFCONSOLEFACTORY_H

#include "guiconsolefactory.h"
#include "olfconsole_forward.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{
namespace factory
{

class OlfConsoleFactory : public plugframe::guiconsole::factory::GuiConsoleFactory
{
public:
    OlfConsoleFactory();
    ~OlfConsoleFactory() override;

public:
    virtual OlfLoginController *createOlfLoginController(bundle::OlfConsole& console,
                                                         int maxLoginAttempts);
    virtual OlfMonitoredObservablesController *createOlfMonitoredObservablesController(bundle::OlfConsole& console,
                                                                                       PageViewLayout monitoringViewLayout);
};

} //namespace factory
} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFCONSOLEFACTORY_H
