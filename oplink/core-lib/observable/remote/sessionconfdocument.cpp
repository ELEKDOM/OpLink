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

#include <QFile>
#include "sessionconfdocument.h"
#include "sessionconfhook.h"

oplink::SessionConfDocument::SessionConfDocument(plugframe::XmlBrowserHook& browserHook):
    plugframe::XmlDocument{browserHook}
{

}

oplink::SessionConfDocument::~SessionConfDocument()
{

}

QString oplink::SessionConfDocument::rootNodeName()
{
    return QStringLiteral("remotemonitoring");
}

bool oplink::SessionConfDocument::_browse()
{
    bool                      ret{true};
    oplink::SessionConfHook& loader{dynamic_cast<oplink::SessionConfHook&>(browserHook())};
    QDomNodeList              monitoredObservableNodes{elementsByTagName(QStringLiteral("monitoredObservable"))};
    int                       l{monitoredObservableNodes.length()};

    for (int i = 0; i < l ; i++)
    {
        QDomNode               node{monitoredObservableNodes.at(i)};
        QDomElement            monitoredObservableElem{node.toElement()};
        QString                obsName{monitoredObservableElem.attribute(QStringLiteral("name"))};
        QString                obsTitle{monitoredObservableElem.attribute(QStringLiteral("title"))};
        QString                obsType{monitoredObservableElem.attribute(QStringLiteral("model-name"))};
        QString                obsLocalisation{monitoredObservableElem.attribute(QStringLiteral("localisation"))};

        loader.beginObservableDeclaration(obsName, obsTitle, obsType, obsLocalisation);
        loader.endObservableDeclaration();
    }

    return ret;
}

