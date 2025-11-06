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

#ifndef D201TELEGRAMFORMAT_H
#define D201TELEGRAMFORMAT_H

#include <QSharedPointer>
#include "d2telegramformat.h"

class D201TelegramFormat : public D2TelegramFormat
{
public:
    D201TelegramFormat();
    ~D201TelegramFormat() override;

public:
    // CMD 0X04 - Actuator Status Response
    bool isCmdActuatorStatusResponse();
    bool getActuatorStatus(quint8& channel, bool& value);
    // CMD 0X07 - Actuator Measurement Response
    bool isCmdActuatorMeasurementResponse();
    bool getActuatorMeasurementValue(quint8& channel, quint32& value, QString& unit);
    // CMD 0X0A - Actuator Pilot Wire Mode Response
    bool isCmdActuatorPilotWireModeResponse();
    bool getActuatorPilotWireMode(quint8& mode);

private:
    static const quint8 CMD_ACTUATOR_STATUS_RESPONSE = 0x04;
    static const quint8 CMD_ACTUATOR_PILOT_WIRE_MODE_RESPONSE = 0x0A;
    static const quint8 CMD_ACTUATOR_MEASUREMENT_RESPONSE = 0x07;

private:
    quint8 getCmd();
};
using QspD201TelegramFormat = QSharedPointer<D201TelegramFormat>;
#endif // D201TELEGRAMFORMAT_H
