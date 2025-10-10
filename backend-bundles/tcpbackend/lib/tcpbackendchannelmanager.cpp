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


#include <QScopedPointer>
#include "tcpbackendchannelmanager.h"
#include "abstract_network_tcp/common/tcpchannelmessage.h"
#include "tcpbackend.h"
#include "tcpbackendlogchannel.h"
#include "network_tcp/messagetype.h"
#include "network_tcp/signinmessage.h"
#include "network_tcp/signinreplymessage.h"
#include "network_tcp/signoutmessage.h"
#include "network_tcp/downloadconfigmessage.h"
#include "network_tcp/readymessage.h"
#include "network_tcp/downloadconfigreplymessage.h"
#include "network_tcp/submitordermessage.h"
#include "network_tcp/statevaluemessage.h"
#include "service-int/loginserviceinterface.h"
#include "observable/remote/subscribesession.h"
#include "logger/pflog.h"

using namespace elekdom::plugframe::core;
using namespace elekdom::oplink;
using namespace elekdom::oplink::tcpbackend::bundle;

TcpBackendChannelManager::TcpBackendChannelManager(tcp::server::bundle::TcpServer& bundle,
                                                   tcp::TcpChannel *channel,
                                                   QObject *parent):
    tcp::server::bundle::TcpServerChannelManager{bundle,channel,parent}
{
    connect(this,SIGNAL(sigDelayedOpenSession(quint32,QString)),SLOT(onDelayedOpenSession(quint32,QString)),Qt::QueuedConnection);
}

TcpBackendChannelManager::~TcpBackendChannelManager()
{

}

TcpBackend &TcpBackendChannelManager::tcpBackendBundle()
{
    return dynamic_cast<TcpBackend&>(bundle());
}

void TcpBackendChannelManager::processMessage(tcp::TcpChannelMessage *input)
{
    if (input)
    {
        quint16 msgType{input->msgType()};

        // message types accepted as input from a client
        switch(msgType)
        {
            case static_cast<quint16>(core::tcp::MessageType::Signin) :
                processSiginMessage(dynamic_cast<core::tcp::SigninMessage*>(input));
            break;

            case static_cast<quint16>(core::tcp::MessageType::Signout) :
                processSignoutMessage(dynamic_cast<core::tcp::SignoutMessage*>(input));
            break;

            case static_cast<quint16>(core::tcp::MessageType::DownloadConfig) :
                processDownloadConfigMessage(dynamic_cast<core::tcp::DownloadConfigMessage*>(input));
            break;

            case static_cast<quint16>(core::tcp::MessageType::Ready) :
                processReadyMessage(dynamic_cast<core::tcp::ReadyMessage*>(input));
            break;

            case static_cast<quint16>(core::tcp::MessageType::SubmitOrder) :
                processSubmitOrderMessage(dynamic_cast<core::tcp::SubmitOrderMessage*>(input));
            break;

            default:
                pfErr(s_TcpBackendLogChannel) << tr("Unknown input message type : ") << msgType;
        }
    }
}

core::tcp::SigninReplyMessage *TcpBackendChannelManager::createSigninSuccessMessage(const QString &identifier, const quint32 &sessionId)
{
    return new core::tcp::SigninReplyMessage(sessionId,identifier,core::tcp::SigninReplyMessage::SigninStatus::Ok);
}

core::tcp::SigninReplyMessage *TcpBackendChannelManager::createSigninFailedMessage(const QString &identifier,
                                                                                   const core::tcp::SigninReplyMessage::SigninStatus& status)
{
    return new core::tcp::SigninReplyMessage(0,identifier,status);
}

core::tcp::SessionStartedMessage *TcpBackendChannelManager::createSessionStartedMessage(const quint32 &sessionId, const qint16 &confId,const QString& profil)
{
    return new core::tcp::SessionStartedMessage(sessionId,confId,profil);
}

core::tcp::DownloadConfigReplyMessage *TcpBackendChannelManager::createDownloadConfigReplyMessage(const quint32 &sessionId, const QString &confContent)
{
    return new  core::tcp::DownloadConfigReplyMessage(sessionId,confContent);
}

core::tcp::StateValueMessage *TcpBackendChannelManager::createStateValueMessage(const quint32 &sessionId,
                                                                                const QString &observableName,
                                                                                const QString &propertyName,
                                                                                const QVariant &value)
{
    return new core::tcp::StateValueMessage(sessionId,observableName,propertyName,value);
}

core::remote::SubscribeSession *TcpBackendChannelManager::createRemoteMonitoringSession(const quint32 &sessionId,
                                                                                        const QString &fileName,
                                                                                        engine::service::ObservableServiceInterface *observableService)
{
    return new core::remote::SubscribeSession(sessionId,
                                              fileName,
                                              observableService);
}

void TcpBackendChannelManager::onDisconnectedFromClient()
{
    closeAllSessions();
}

void TcpBackendChannelManager::onNewState(quint32 sessionId,
                                          elekdom::oplink::core::observable::ObservableName observableName,
                                          elekdom::oplink::core::observable::PropertyName propertyName,
                                          QVariant propertyValue)
{
    QScopedPointer<core::tcp::Message> p;

    p.reset(createStateValueMessage(sessionId,observableName,propertyName,propertyValue));
    sendMessage(*p);
}

void TcpBackendChannelManager::onDelayedOpenSession(quint32 sessionId, QString profil)
{

    plugframe::users::service::LoginServiceInterface *loginServ{tcpBackendBundle().loginService()};
    qint16 confId;
    QScopedPointer<core::tcp::Message> p;
    bool ok;

    ok = openSession(sessionId,profil,loginServ,confId);
    if (ok)
    {
        pfInfo1(s_TcpBackendLogChannel) << tr("Session open : ") << sessionId;
        p.reset(createSessionStartedMessage(sessionId,confId,profil));
    }
    else
    {
        pfErr(s_TcpBackendLogChannel) << tr("Failed to open a new session for id : ") << sessionId;
        p.reset(createSessionStartedMessage(0,0,"")); // return internal server error
    }

    sendMessage(*p); // session started on server
}

void TcpBackendChannelManager::processSiginMessage(core::tcp::SigninMessage *msg)
{
    if (msg)
    {
        plugframe::users::service::LoginServiceInterface *loginServ{tcpBackendBundle().loginService()};
        plugframe::users::service::LoginServiceInterface::LoginStatus loginStatus;
        quint32 sessionId;
        QString profil;
        QScopedPointer<core::tcp::Message> p;
        bool openSession{false};

        if (loginServ != nullptr)
        {
            loginServ->login(msg->frontendItf(),
                             msg->frontendIp(),
                             msg->identifier(),
                             msg->password(),
                             loginStatus,
                             sessionId,
                             profil);

            if (loginStatus == plugframe::users::service::LoginServiceInterface::LoginStatus::Ok)
            {
                if (m_remoteMonitoringSessions.find(sessionId) == m_remoteMonitoringSessions.end())
                {
                    p.reset(createSigninSuccessMessage(msg->identifier(),sessionId));
                    openSession = true;
                }
                else
                {
                    pfErr(s_TcpBackendLogChannel) << tr("Duplicate session Id : ") << sessionId;
                    p.reset(createSigninFailedMessage(msg->identifier(),
                                                      core::tcp::SigninReplyMessage::SigninStatus::InternalErr));
                }
            }
            else
            {
                p.reset(createSigninFailedMessage(msg->identifier(),
                                                  static_cast<core::tcp::SigninReplyMessage::SigninStatus>(loginStatus)));
            }
        }
        else
        {
            pfErr(s_TcpBackendLogChannel) << tr("Users login service not found!");
            p.reset(createSigninFailedMessage(msg->identifier(),
                                              core::tcp::SigninReplyMessage::SigninStatus::InternalErr));
        }

        sendMessage(*p); //sigin reply

        if (openSession)
        {
            emit sigDelayedOpenSession(sessionId,profil);  // queued connection !
        }


    }//if (msg)
}

void TcpBackendChannelManager::processSignoutMessage(core::tcp::SignoutMessage *msg)
{
    if (msg)
    {
        quint32 sid{msg->sessionId()};
        closeSession(sid);
    }
}

void TcpBackendChannelManager::processDownloadConfigMessage(core::tcp::DownloadConfigMessage *msg)
{
    if (msg)
    {
        QScopedPointer<core::tcp::Message> p;
        QString configContent;
        quint32 sid{msg->sessionId()};

        configContent = confContentFromSession(sid);
        p.reset(createDownloadConfigReplyMessage(sid,configContent));
        sendMessage(*p);
    }
}

void TcpBackendChannelManager::processReadyMessage(core::tcp::ReadyMessage *msg)
{
    if (msg)
    {
        quint32 sid{msg->sessionId()};

        enableSession(sid);
    }
}

void TcpBackendChannelManager::processSubmitOrderMessage(core::tcp::SubmitOrderMessage *msg)
{
    if (msg)
    {
        quint32 sid{msg->sessionId()};
        submitOrderToSession(sid,msg->order());
    }
}

elekdom::plugframe::users::service::LoginServiceInterface *TcpBackendChannelManager::loginService()
{
    TcpBackend& tcpBundle{dynamic_cast<TcpBackend&>(bundle())};

    return tcpBundle.loginService();
}

bool TcpBackendChannelManager::openSession(const quint32& sessionId,
                               const QString& profil,
                               elekdom::plugframe::users::service::LoginServiceInterface *lService,
                               qint16& confId)
{
    bool ret{false};
    engine::service::ObservableServiceInterface *oService{tcpBackendBundle().observableService()};
    QString fileName{lService->absoluteUserConfFileName(profil)};
    core::remote::QspSubscribeSession rs;

    rs.reset(createRemoteMonitoringSession(sessionId,fileName,oService));
    m_remoteMonitoringSessions.insert(sessionId,rs);
    bool ok = connect(rs.get(),
            SIGNAL(newState(quint32,elekdom::oplink::core::observable::ObservableName,elekdom::oplink::core::observable::PropertyName,QVariant)),
            SLOT(onNewState(quint32,elekdom::oplink::core::observable::ObservableName,elekdom::oplink::core::observable::PropertyName,QVariant)));
    if (!ok)
    {
        pfErr(s_TcpBackendLogChannel) << tr("Can't connect newState signal from remote monit:oring session!");
    }
    ret = rs->open(confId);

    return ret;
}

void TcpBackendChannelManager::enableSession(const quint32 &sessionId)
{
    core::remote::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->enableMonitoring();
    }
}

void TcpBackendChannelManager::closeAllSessions()
{
    QList<quint32> listKeys{m_remoteMonitoringSessions.keys()};

    for (int i = 0; i < listKeys.size(); i++)
    {
        closeSession(listKeys.at(i));
    }
}

void TcpBackendChannelManager::closeSession(const quint32 &sessionId)
{
    core::remote::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->close();
        m_remoteMonitoringSessions.remove(sessionId);
    }
}

QString TcpBackendChannelManager::confContentFromSession(const quint32 &sessionId)
{
    QString ret;
    core::remote::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        ret = session->confContent();
    }

    return ret;
}

void TcpBackendChannelManager::submitOrderToSession(const quint32 &sessionId, const QString &order)
{
    core::remote::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->submitOrder(order);
    }
}

