// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
//
// This file is part of PlugFrame.
//
// PlugFrame is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// PlugFrame is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//
#ifndef OBSERVABLEPUBLISHERMESSAGESCODEC_H
#define OBSERVABLEPUBLISHERMESSAGESCODEC_H

#include "network/channel/messagescodec.h"

class ObservablePublisherMessagesCodec : public plugframe::MessagesCodec
{
    Q_OBJECT

public:
    explicit ObservablePublisherMessagesCodec(QObject *parent = nullptr);

signals:
    void signinMessage(QString frontendItf,QString frontendIp,QString identifier,QString password);
    void signoutMessage(quint32 sessionId);
    void downloadConfigMessage(quint32 sessionId);
    void readyMessage(quint32 sessionId);
    void submitOrderMessage(quint32 sessionId,QString order);

protected:
    bool extractArgsFromStream(quint16 msgId,QDataStream& input) override;

private:
    bool extractSiginMessage(QDataStream& input);
    bool extractSignoutMessage(QDataStream& input);
    bool extractDownloadConfigMessage(QDataStream& input);
    bool extractReadyMessage(QDataStream& input);
    bool extractSubmitOrderMessage(QDataStream& input);
};

#endif // OBSERVABLEPUBLISHERMESSAGESCODEC_H
