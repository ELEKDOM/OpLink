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

#ifndef HIGHOBSERVABLECONFDOCUMENT_H
#define HIGHOBSERVABLECONFDOCUMENT_H

#include <QSharedPointer>
#include "xmldom/xmldocument.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HighObservableConfDocument : public plugframe::XmlDocument
{
protected:
    static QString nameAttr() {return QStringLiteral("name");}
    static QString propertyAttr() {return QStringLiteral("property");}
    static QString localisationAttr() {return QStringLiteral("localisation");}
    static QString titleAttr() {return QStringLiteral("title");}
    static QString stateAttr() {return QStringLiteral("state");}

public:
    HighObservableConfDocument(HighObservableLoaderHook& browserHook);
    ~HighObservableConfDocument() override;
};
using QspVirtualEquipmentConfDocument = QSharedPointer<HighObservableConfDocument>;
}//namespace oplink
#endif // HIGHOBSERVABLECONFDOCUMENT_H
