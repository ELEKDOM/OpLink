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

#ifndef CORELIBTYPE_H
#define CORELIBTYPE_H

#include "olcore-lib_export.h"

namespace oplink
{
class OLCORE_LIB_EXPORT Type
{
public:
    // SENSORS
    static QString TEMPERATURE_HUMIDITY_SENSOR;
    static QString DOOR_SENSOR;
    static QString WINDOW_SENSOR;
    static QString ROCKER_SWITCH_2_BUTTONS;

    // ACTUATORS
    static QString ACTUATOR_2_OUTPUTS_BINARY;
    static QString ONOFF_SMART_PLUG;
    static QString ONOFF_SMART_PLUG_MEASUREMENT;
    static QString PW_ACTUATOR;
    static QString PW_ACTUATOR_MEASUREMENT;

    // LOADS
    static QString BASIC_ELECTRIC_HEATING;
    static QString PW_ELECTRIC_HEATING;
    static QString PW_ELECTRIC_HEATING_MEASUREMENT;
    static QString ONOFF_LIGHTING;
};
}//namespace oplink
#endif // CORELIBTYPE_H
