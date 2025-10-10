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


#include <QTextStream>
#include "unsubscribecmdprocessor.h"
#include "observable/observablenames.h"
#include "olconsole.h"

using namespace elekdom::oplink::console::cmd;


UnsubscribeCmdProcessor::UnsubscribeCmdProcessor(const QString &logChannel,
                                                 bundle::OlConsole &console):
    OlCmdProcessor{logChannel,
                    console,
                    "unsubscribe",
                    "Se désabonne des changements d'états d'un observable"}
{

}

UnsubscribeCmdProcessor::~UnsubscribeCmdProcessor()
{

}

bool UnsubscribeCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)
    QTextStream                         stream(stdin);
    core::observable::ObservableName name;

    console().print(QObject::tr("Format d'une commande : observable_name\n"));
    console().print(QObject::tr("<Entrée> pour quitter ce mode\n"));
    do
    {
        stream.readLineInto(&name);

        if (!name.isEmpty())
        {
            if (!m_olConsole.unsubscribe(name))
            {
                console().print(QObject::tr("Observable non enregistré %1\n").arg(name));
            }
        }

    }while(!name.isEmpty());

    return true;
}
