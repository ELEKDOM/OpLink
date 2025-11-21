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
#include "subscribecmdprocessor.h"
#include "olconsole.h"
#include "subscribecmdprocessorhook.h"

SubscribeCmdProcessor::SubscribeCmdProcessor(const QString &logChannel,
                                             OlConsole &console):
    OlCmdProcessor{logChannel,
                    console,
                    "subscribe",
                    "S'abonne aux changements d'états d'un observable"},
    m_hook{new SubscribeCmdProcessorHook(*this)}
{

}

SubscribeCmdProcessor::~SubscribeCmdProcessor()
{
    delete m_hook;
}

oplink::ObservableSubscriber *SubscribeCmdProcessor::observableSubscriber()
{
    return m_hook;
}

void SubscribeCmdProcessor::stateChange(const oplink::ObservableName &observableName,
                                        const oplink::PropertyName &propertyName,
                                        QVariant propertyValue)
{
    console().print(QObject::tr("notification de changement d'état : %1 %2 %3\n").arg(observableName, propertyName, propertyValue.toString()));
}

bool SubscribeCmdProcessor::exec(const RawCmd &cmd)
{
    Q_UNUSED(cmd)
    QTextStream                         stream(stdin);
    oplink::ObservableName name;

    console().print(QObject::tr("Format d'une commande : observable_name\n"));
    console().print(QObject::tr("<Entrée> pour quitter ce mode\n"));
    do
    {
        stream.readLineInto(&name);

        if (!name.isEmpty())
        {
            if (!m_olConsole.subscribe(name))
            {
                console().print(QObject::tr("Observable non enregistré %1\n").arg(name));
            }
        }

    }while(!name.isEmpty());

    return true;
}
