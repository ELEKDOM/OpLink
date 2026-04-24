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
#include "values.h"
#include "command/command-names.h"

bool oplink::Values::STATE_ON = true;
bool oplink::Values::STATE_OFF = false;
quint8 oplink::Values::PW_MODE_STOP = 0x00;
quint8 oplink::Values::PW_MODE_COMFORT = 0x01;
quint8 oplink::Values::PW_MODE_COMFORT_1 = 0x02;
quint8 oplink::Values::PW_MODE_COMFORT_2 = 0x03;
quint8 oplink::Values::PW_MODE_ECO = 0x04;
quint8 oplink::Values::PW_MODE_ANTI_FREEZE = 0x05;
QString oplink::Values::ENERGY_Ws = QStringLiteral("Ws");
QString oplink::Values::ENERGY_Wh = QStringLiteral("Wh");
QString oplink::Values::ENERGY_KWh = QStringLiteral("KWh");
QString oplink::Values::POWER_W = QStringLiteral("W");
QString oplink::Values::POWER_KW = QStringLiteral("KW");

QString oplink::Values::TRIGGER_MODE_ONDEMAND = QStringLiteral("ondemand");
QString oplink::Values::TRIGGER_MODE_PLANNED = QStringLiteral("planned");

QString oplink::Values::convertPWM2str(quint8 pwm)
{
    QString ret;

    if (PW_MODE_COMFORT == pwm)
    {
        ret = CommandArgs::COMFORT;
    }
    else if(PW_MODE_COMFORT_1 == pwm)
    {
        ret = CommandArgs::COMFORT_1;
    }
    else if(PW_MODE_COMFORT_2 == pwm)
    {
        ret = CommandArgs::COMFORT_2;
    }
    else if(PW_MODE_ECO == pwm)
    {
        ret = CommandArgs::ECO;
    }
    else if(PW_MODE_ANTI_FREEZE == pwm)
    {
        ret = CommandArgs::NOFROST;
    }
    else
    {
        ret = CommandArgs::OFF;
    }

    return ret;
}

quint8 oplink::Values::convertStr2pwm(const QString &str)
{
    quint8 ret;

    if (CommandArgs::COMFORT == str)
    {
        ret = PW_MODE_COMFORT;
    }
    else if(CommandArgs::COMFORT_1 == str)
    {
        ret = PW_MODE_COMFORT_1;
    }
    else if(CommandArgs::COMFORT_2 == str)
    {
        ret = PW_MODE_COMFORT_2;
    }
    else if(CommandArgs::ECO == str)
    {
        ret = PW_MODE_ECO;
    }
    else if(CommandArgs::NOFROST == str)
    {
        ret = PW_MODE_ANTI_FREEZE;
    }
    else
    {
        ret = PW_MODE_STOP;
    }

    return ret;
}
