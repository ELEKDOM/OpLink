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

#include <QString>
#include <QStringLiteral>
#include "type.h"

// SENSORS
QString oplink::Type::TEMPERATURE_HUMIDITY_SENSOR = QStringLiteral("temperature_humidity_sensor");
QString oplink::Type::DOOR_SENSOR = QStringLiteral("door_sensor");
QString oplink::Type::WINDOW_SENSOR = QStringLiteral("window_sensor");
QString oplink::Type::ROCKER_SWITCH_2_BUTTONS = QStringLiteral("rocker_switch_2_buttons");

// ACTUATORS
QString oplink::Type::ACTUATOR_2_OUTPUTS_BINARY = QStringLiteral("actuator_2_outputs_binary");
QString oplink::Type::ONOFF_SMART_PLUG = QStringLiteral("onoff_smart_plug");
QString oplink::Type::ONOFF_SMART_PLUG_MEASUREMENT = QStringLiteral("onoff_smart_plug_measurement");
QString oplink::Type::PW_ACTUATOR = QStringLiteral("pw_actuator");
QString oplink::Type::PW_ACTUATOR_MEASUREMENT = QStringLiteral("pw_actuator_measurement");

// LOADS
QString oplink::Type::BASIC_ELECTRIC_HEATING = QStringLiteral("basic_electriic_heating");
QString oplink::Type::PW_ELECTRIC_HEATING = QStringLiteral("pw_electric_heating");
QString oplink::Type::PW_ELECTRIC_HEATING_MEASUREMENT = QStringLiteral("pw_electric_heating_measurement");
QString oplink::Type::ONOFF_LIGHTING = QStringLiteral("onoff_lighting");
