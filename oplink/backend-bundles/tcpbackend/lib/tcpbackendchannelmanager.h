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

#ifndef TCPBACKENDCHANNELMANAGER_H
#define TCPBACKENDCHANNELMANAGER_H

#include <QHash>
#include "service-int/observableserviceinterface.h"
#include "service-int/loginserviceinterface.h"
#include "observable/remote/subscribesession.h"
#include "abstract_network_tcp/server/tcpserverchannelmanager.h"
#include "network_tcp/signinreplymessage.h"
#include "tcpbackend_forward.h"
#include "olcore-lib_forward.h"

class TcpBackendChannelManager : public plugframe::TcpServerChannelManager
{
    Q_OBJECT

public:
    TcpBackendChannelManager(plugframe::TcpServer& bundle,
                             plugframe::TcpChannel *channel,
                             QObject *parent = nullptr);
    ~TcpBackendChannelManager() override;

protected:
    TcpBackend& tcpBackendBundle();
    void processMessage(plugframe::TcpChannelMessage *input) override;
    virtual oplink::SigninReplyMessage *createSigninSuccessMessage(const QString& identifier,
                                                                   const quint32& sessionId);
    virtual oplink::SigninReplyMessage *createSigninFailedMessage(const QString& identifier,
                                                                  const oplink::SigninReplyMessage::SigninStatus& status);
    virtual oplink::SessionStartedMessage *createSessionStartedMessage(const quint32 &sessionId,
                                                                       const qint16& confId,
                                                                       const QString& profil);
    virtual oplink::DownloadConfigReplyMessage *createDownloadConfigReplyMessage(const quint32 &sessionId,
                                                                                 const QString& confContent);
    virtual oplink::StateValueMessage *createStateValueMessage(const quint32& sessionId,
                                                               const QString& observableName,
                                                               const QString& propertyName,
                                                               const QVariant& value);
    virtual oplink::SubscribeSession *createRemoteMonitoringSession(const quint32 &sessionId,
                                                                    const QString& fileName,
                                                                    oplink::ObservableServiceInterface *observableService);
     void onDisconnectedFromClient() override;

protected slots:
    void onNewState(quint32 sessionId,
                    oplink::ObservableName observableName,
                    oplink::PropertyName propertyName,
                    QVariant propertyValue);

signals:
    void sigDelayedOpenSession(quint32 sessionId,QString profil);

private slots:
    void onDelayedOpenSession(quint32 sessionId,QString profil);

private:
    void processSiginMessage(oplink::SigninMessage* msg);
    void processSignoutMessage(oplink::SignoutMessage* msg);
    void processDownloadConfigMessage(oplink::DownloadConfigMessage* msg);
    void processReadyMessage(oplink::ReadyMessage* msg);
    void processSubmitOrderMessage(oplink::SubmitOrderMessage* msg);
    plugframe::LoginServiceInterface *loginService();
    bool openSession(const quint32& sessionId,
                     const QString& profil,
                     plugframe::LoginServiceInterface *lService,
                     qint16& confId);
    void enableSession(const quint32& sessionId);
    void closeAllSessions();
    void closeSession(const quint32& sessionId);
    QString confContentFromSession(const quint32& sessionId);
    void submitOrderToSession(const quint32& sessionId,const QString& order);

private:
    QHash<quint32, oplink::QspSubscribeSession> m_remoteMonitoringSessions;
};

#endif // TCPBACKENDCHANNELMANAGER_H
