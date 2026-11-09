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
#ifndef OBSERVABLEPUBLISHERCLIENTCONNECTION_H
#define OBSERVABLEPUBLISHERCLIENTCONNECTION_H

#include "observablepublisher.h"
#include "network/backend/clientconnection.h"
#include "network/channel/messagetype.h"
#include "observable/remote/subscribesession.h"
class ObservablePublisherClientConnection : public plugframe::ClientConnection
{
    Q_OBJECT

public:
    explicit ObservablePublisherClientConnection(plugframe::Publisher *bundle,plugframe::MessagesCodec *codec,QObject *parent = nullptr);
    ~ObservablePublisherClientConnection() override;

signals:
    void delayedOpenSession(quint32 sessionId,QString profil);

private slots:
    void onSigninMessage(QString frontendItf,QString frontendIp,QString identifier,QString password);
    void onSignoutMessage(quint32 sessionId);
    void onDownloadConfigMessage(quint32 sessionId);
    void onReadyMessage(quint32 sessionId);
    void onSubmitOrderMessage(quint32 sessionId,QString order);
    void onDelayedOpenSession(quint32 sessionId,QString profil);
    void onNewState(quint32 sessionId,oplink::ObservableName observableName,oplink::PropertyName propertyName,QVariant propertyValue);

protected:
    ObservablePublisher *observablePublisherBundle();
    virtual oplink::SubscribeSession *createRemoteMonitoringSession(const quint32 &sessionId,const QString& fileName,oplink::ObservableServiceInterface *observableService);

private:
    bool openSession(const quint32& sessionId,const QString& profil,plugframe::LoginServiceInterface *lService,qint16& confId);
    void closeSession(const quint32& sessionId);
    void closeAllSessions();
    QString confContentFromSession(const quint32& sessionId);
    void enableSession(const quint32& sessionId);
    void submitOrderToSession(const quint32& sessionId,const QString& order);
    plugframe::OutputStream *createEmbeddedSigninSuccessMessage(const QString& identifier,const quint32& sessionId);
    plugframe::OutputStream *createEmbeddedSigninFailedMessage(const QString &identifier,const oplink::SigninStatus& status);
    plugframe::OutputStream *createEmbeddedSessionStartedMessage(const quint32 &sessionId,const qint16& confId,const QString& profil);
    plugframe::OutputStream *createEmbeddedDownloadConfigReplyMessage(const quint32 &sessionId,const QString& confContent);
    plugframe::OutputStream *createEmbeddedStateValueMessage(const quint32& sessionId,const QString& observableName,const QString& propertyName,const QVariant& value);
    plugframe::OutputStream *createEmbeddedSignoutMessage(const quint32& sessionId);

private:
    QHash<quint32, oplink::QspSubscribeSession> m_remoteMonitoringSessions;
};

#endif // OBSERVABLEPUBLISHERCLIENTCONNECTION_H
