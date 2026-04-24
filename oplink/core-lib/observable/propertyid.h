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

#ifndef PROPERTYID_H
#define PROPERTYID_H

#include "olcore-lib_export.h"

namespace oplink
{

using PropertyName = QString;

class OLCORE_LIB_EXPORT PropertyId
{
public:
    // mandatory property
    static const PropertyName P_NAME;
    static const PropertyName P_MODEL;
    static const PropertyName P_LOCALISATION;

    // for VirtualEquipment
    static const PropertyName P_RUNNING;
    static const PropertyName P_TRIGGER_MODE;
    static const PropertyName P_SCHEDULER_XML_DEF;

    // for HeatingManager
    static const PropertyName P_SETPOINT;
    static const PropertyName P_DEROGATED;
    static const PropertyName P_WCLOSED;
    static const PropertyName P_TEMPERATURE;

    // for compound name of a group property
    static PropertyName groupPropertyName(quint8 groupIdx, const PropertyName& propertyName);
    static PropertyName groupPropertyName(const QString& groupPrefix, const PropertyName& propertyName);
    static QString extractGroupPrefix(const PropertyName& compoundName);
    static QString groupPrefix(quint8 groupIdx);
    static PropertyName extractPropertyName(const PropertyName& compoundName);
    static bool isGroupProperty(const PropertyName& compoundName,quint8& groupIdx,PropertyName& propertyName);
};
}//namespace oplink
#endif // PROPERTYID_H
