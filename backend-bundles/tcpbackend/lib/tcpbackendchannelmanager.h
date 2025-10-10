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
#include "abstract_network_tcp/server/tcpserverchannelmanager.h"
#include "network_tcp/signinreplymessage.h"
#include "network_tcp/sessionstartedmessage.h"
#include "network_tcp/downloadconfigreplymessage.h"
#include "network_tcp/statevaluemessage.h"
#include "olcore-lib_forward.h"
#include "olcore-backend-lib_forward.h"
#include "tcpbackend.h"
#include "tcpbackend_forward.h"

namespace elekdom
{
namespace oplink
{
namespace tcpbackend
{
namespace bundle
{

class TcpBackendChannelManager : public plugframe::core::tcp::server::bundle::TcpServerChannelManager
{
    Q_OBJECT

public:
    TcpBackendChannelManager(plugframe::core::tcp::server::bundle::TcpServer& bundle,
                             plugframe::core::tcp::TcpChannel *channel,
                             QObject *parent = nullptr);
    ~TcpBackendChannelManager() override;

protected:
    TcpBackend& tcpBackendBundle();
    void processMessage(plugframe::core::tcp::TcpChannelMessage *input) override;
    virtual core::tcp::SigninReplyMessage *createSigninSuccessMessage(const QString& identifier,
                                                                      const quint32& sessionId);
    virtual core::tcp::SigninReplyMessage *createSigninFailedMessage(const QString& identifier,
                                                                     const core::tcp::SigninReplyMessage::SigninStatus& status);
    virtual core::tcp::SessionStartedMessage *createSessionStartedMessage(const quint32 &sessionId,
                                                                          const qint16& confId,
                                                                          const QString& profil);
    virtual core::tcp::DownloadConfigReplyMessage *createDownloadConfigReplyMessage(const quint32 &sessionId,
                                                                                    const QString& confContent);
    virtual core::tcp::StateValueMessage *createStateValueMessage(const quint32& sessionId,
                                                                  const QString& observableName,
                                                                  const QString& propertyName,
                                                                  const QVariant& value);
    virtual core::remote::SubscribeSession *createRemoteMonitoringSession(const quint32 &sessionId,
                                                                          const QString& fileName,
                                                                          engine::service::ObservableServiceInterface *observableService);
     void onDisconnectedFromClient() override;

protected slots:
    void onNewState(quint32 sessionId,
                    elekdom::oplink::core::observable::ObservableName observableName,
                    elekdom::oplink::core::observable::PropertyName propertyName,
                    QVariant propertyValue);

signals:
    void sigDelayedOpenSession(quint32 sessionId,QString profil);

private slots:
    void onDelayedOpenSession(quint32 sessionId,QString profil);

private:
    void processSiginMessage(core::tcp::SigninMessage* msg);
    void processSignoutMessage(core::tcp::SignoutMessage* msg);
    void processDownloadConfigMessage(core::tcp::DownloadConfigMessage* msg);
    void processReadyMessage(core::tcp::ReadyMessage* msg);
    void processSubmitOrderMessage(core::tcp::SubmitOrderMessage* msg);
    plugframe::users::service::LoginServiceInterface *loginService();
    bool openSession(const quint32& sessionId,
                     const QString& profil,
                     elekdom::plugframe::users::service::LoginServiceInterface *lService,
                     qint16& confId);
    void enableSession(const quint32& sessionId);
    void closeAllSessions();
    void closeSession(const quint32& sessionId);
    QString confContentFromSession(const quint32& sessionId);
    void submitOrderToSession(const quint32& sessionId,const QString& order);

private:
    QHash<quint32, oplink::core::remote::QspSubscribeSession> m_remoteMonitoringSessions;
};

} //namespace bundle
} //namespace tcpbackend
} //namespace oplink
} //namespace elekdom

#endif // TCPBACKENDCHANNELMANAGER_H
