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

#include <QRegularExpression>
#include "propertyid.h"

const oplink::PropertyName oplink::PropertyId::P_NAME {"name"};
const oplink::PropertyName oplink::PropertyId::P_MODEL {"model"};
const oplink::PropertyName oplink::PropertyId::P_LOCALISATION {"localisation"};
const oplink::PropertyName oplink::PropertyId::P_RUNNING {"run"};
const oplink::PropertyName oplink::PropertyId::P_TRIGGER_MODE {"tmode"};
const oplink::PropertyName oplink::PropertyId::P_SETPOINT{"setpoint"};
const oplink::PropertyName oplink::PropertyId::P_DEROGATED{"derogated"};
const oplink::PropertyName oplink::PropertyId::P_WCLOSED{"wclosed"};
const oplink::PropertyName oplink::PropertyId::P_TEMPERATURE{"temperature"};
const oplink::PropertyName oplink::PropertyId::P_SCHEDULER_XML_DEF{"planning"};

QString oplink::PropertyId::groupPropertyName(const QString &groupName, const PropertyName &propertyName)
{
    return (groupName + '{' + propertyName + '}');
}

QString oplink::PropertyId::extractGroupName(const QString &compoundName)
{
    QString ret;
    QRegularExpression re("^\\w+\\s*\\w*");

    QRegularExpressionMatch match = re.match(compoundName);
    if (match.hasMatch()) {
        ret = match.captured(0); // group name part
    }

    return ret;
}

QString oplink::PropertyId::extractPropertyName(const QString &compoundName)
{
    QString ret;
    QRegularExpression re("{(\\w+)}$");

    QRegularExpressionMatch match = re.match(compoundName);
    if (match.hasMatch()) {
        ret = match.captured(1); // property name part
    }

    return ret;
}
