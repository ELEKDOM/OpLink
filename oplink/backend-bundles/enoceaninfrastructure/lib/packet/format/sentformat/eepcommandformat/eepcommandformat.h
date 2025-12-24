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

#ifndef EEPCOMMANDFORMAT_H
#define EEPCOMMANDFORMAT_H

#include <QSharedPointer>
#include "packet/format/sentformat/esp3sentpacketformat.h"

class EepCommandFormat : public Esp3SentPacketFormat
{
public:
    EepCommandFormat(quint16 dataPayload, quint8 optionalLenght, quint8 rorg);
    ~EepCommandFormat() override;

public:
    void insertSenderId(quint32 senderId);
    void insertDestinationId(quint32 destinationId);

protected:
    void fillInData() override;
    QspResponseFormat getExpectedResponseFormat(const QspEsp3Packet& responsePacket) override;

private:
    quint16 m_dataPayload;
    quint8 m_rorg;
};
using QspEepCommandFormat = QSharedPointer<EepCommandFormat>;
#endif // EEPCOMMANDFORMAT_H
