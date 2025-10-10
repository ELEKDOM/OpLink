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
#include "submitcmdprocessor.h"
#include "command/command-names.h"
#include "olconsole.h"

using namespace elekdom::oplink::console::cmd;
using namespace elekdom::oplink::core::command;

SubmitCmdProcessor::SubmitCmdProcessor(const QString &logChannel,
                                       bundle::OlConsole &console):
    OlCmdProcessor{logChannel,
                    console,
                    "submit",
                    "Transmets une commande à un observable"}
{

}

SubmitCmdProcessor::~SubmitCmdProcessor()
{

}

bool SubmitCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)
    QTextStream stream(stdin);
    StrOrder     order;

    console().print(QObject::tr("Format d'une commande : order observable_name [property_name value]\n"));
    console().print(QObject::tr("<Entrée> pour quitter ce mode\n"));
    do
    {
        stream.readLineInto(&order);

        if (!order.isEmpty())
        {
            if (!m_olConsole.submitOrder(order))
            {
                console().print(QObject::tr("Erreur dans la commande %1\n").arg(order));
            }
        }

    }while(!order.isEmpty());

    return true;
}
