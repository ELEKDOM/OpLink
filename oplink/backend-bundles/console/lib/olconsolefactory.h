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

#ifndef OLCONSOLEFACTORY_H
#define OLCONSOLEFACTORY_H

#include "consolefactory.h"
#include "olconsole_forward.h"

class OlConsoleFactory : public ConsoleFactory
{
public:
    OlConsoleFactory();
    ~OlConsoleFactory() override;

public:
    virtual QspCmdProcessor createSubmitCmdProcessor(const QString& logChannel,
                                                     OlConsole& console);
    virtual QspCmdProcessor createSubscribeCmdProcessor(const QString& logChannel,
                                                        OlConsole& console);
    virtual QspCmdProcessor createUnsubscribeCmdProcessor(const QString& logChannel,
                                                          OlConsole& console);
};
#endif // OLCONSOLEFACTORY_H
