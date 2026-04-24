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

#ifndef VALUES_H
#define VALUES_H

#include "olcore-lib_export.h"

namespace oplink
{
class OLCORE_LIB_EXPORT Values
{
public:
// For Observable
    static bool STATE_ON;
    static bool STATE_OFF;
    static quint8 PW_MODE_STOP;
    static quint8 PW_MODE_COMFORT;
    static quint8 PW_MODE_COMFORT_1;
    static quint8 PW_MODE_COMFORT_2;
    static quint8 PW_MODE_ECO;
    static quint8 PW_MODE_ANTI_FREEZE;
    static QString ENERGY_Ws;
    static QString ENERGY_Wh;
    static QString ENERGY_KWh;
    static QString POWER_W;
    static QString POWER_KW;

// For HighObservable
    static QString TRIGGER_MODE_ONDEMAND;
    static QString TRIGGER_MODE_PLANNED;

// For HeatingManager

// Tools
    static QString convertPWM2str(quint8 pwm);
    static quint8 convertStr2pwm(const QString& str);

};
}//namespace oplink
#endif // VALUES_H
