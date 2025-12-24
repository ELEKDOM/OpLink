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
#include "tcpbackendlogchannel.h"
#include "logger/pflog.h"
#include "tcpbackendchannelmanager.h"
#include "tcpbackend.h"
#include "network_tcp/messagetype.h"
#include "network_tcp/signinmessage.h"
#include "network_tcp/signoutmessage.h"
#include "network_tcp/downloadconfigmessage.h"
#include "network_tcp/downloadconfigreplymessage.h"
#include "network_tcp/readymessage.h"
#include "network_tcp/submitordermessage.h"
#include "network_tcp/sessionstartedmessage.h"
#include "network_tcp/statevaluemessage.h"

TcpBackendChannelManager::TcpBackendChannelManager(plugframe::TcpServer& bundle,
                                                   plugframe::TcpChannel *channel,
                                                   QObject *parent):
    plugframe::TcpServerChannelManager{bundle,channel,parent}
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

void TcpBackendChannelManager::processMessage(plugframe::TcpChannelMessage *input)
{
    if (input)
    {
        quint16 msgType{input->msgType()};

        // message types accepted as input from a client
        switch(msgType)
        {
        case static_cast<quint16>(oplink::MessageType::Signin) :
                processSiginMessage(dynamic_cast<oplink::SigninMessage*>(input));
            break;

            case static_cast<quint16>(oplink::MessageType::Signout) :
                processSignoutMessage(dynamic_cast<oplink::SignoutMessage*>(input));
            break;

            case static_cast<quint16>(oplink::MessageType::DownloadConfig) :
                processDownloadConfigMessage(dynamic_cast<oplink::DownloadConfigMessage*>(input));
            break;

            case static_cast<quint16>(oplink::MessageType::Ready) :
                processReadyMessage(dynamic_cast<oplink::ReadyMessage*>(input));
            break;

            case static_cast<quint16>(oplink::MessageType::SubmitOrder) :
                processSubmitOrderMessage(dynamic_cast<oplink::SubmitOrderMessage*>(input));
            break;

            default:
                pfErr(s_TcpBackendLogChannel) << tr("Unknown input message type : ") << msgType;
        }
    }
}

oplink::SigninReplyMessage *TcpBackendChannelManager::createSigninSuccessMessage(const QString &identifier,
                                                                                 const quint32 &sessionId)
{
    return new oplink::SigninReplyMessage(sessionId,identifier,oplink::SigninReplyMessage::SigninStatus::Ok);
}

oplink::SigninReplyMessage *TcpBackendChannelManager::createSigninFailedMessage(const QString &identifier,
                                                                                const oplink::SigninReplyMessage::SigninStatus& status)
{
    return new oplink::SigninReplyMessage(0,identifier,status);
}

oplink::SessionStartedMessage *TcpBackendChannelManager::createSessionStartedMessage(const quint32 &sessionId,
                                                                                     const qint16 &confId,
                                                                                     const QString& profil)
{
    return new oplink::SessionStartedMessage(sessionId,confId,profil);
}

oplink::DownloadConfigReplyMessage *TcpBackendChannelManager::createDownloadConfigReplyMessage(const quint32 &sessionId,
                                                                                               const QString &confContent)
{
    return new  oplink::DownloadConfigReplyMessage(sessionId,confContent);
}

oplink::StateValueMessage *TcpBackendChannelManager::createStateValueMessage(const quint32 &sessionId,
                                                                             const QString &observableName,
                                                                             const QString &propertyName,
                                                                             const QVariant &value)
{
    return new oplink::StateValueMessage(sessionId,observableName,propertyName,value);
}

oplink::SubscribeSession *TcpBackendChannelManager::createRemoteMonitoringSession(const quint32 &sessionId,
                                                                                  const QString &fileName,
                                                                                  oplink::ObservableServiceInterface *observableService)
{
    return new oplink::SubscribeSession(sessionId,
                                        fileName,
                                        observableService);
}

void TcpBackendChannelManager::onDisconnectedFromClient()
{
    closeAllSessions();
}

void TcpBackendChannelManager::onNewState(quint32 sessionId,
                                          oplink::ObservableName observableName,
                                          oplink::PropertyName propertyName,
                                          QVariant propertyValue)
{
    QScopedPointer<oplink::Message> p;

    p.reset(createStateValueMessage(sessionId,observableName,propertyName,propertyValue));
    sendMessage(*p);
}

void TcpBackendChannelManager::onDelayedOpenSession(quint32 sessionId, QString profil)
{

    plugframe::LoginServiceInterface *loginServ{tcpBackendBundle().loginService()};
    qint16 confId;
    QScopedPointer<oplink::Message> p;
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

void TcpBackendChannelManager::processSiginMessage(oplink::SigninMessage *msg)
{
    if (msg)
    {
        plugframe::LoginServiceInterface *loginServ{tcpBackendBundle().loginService()};
        plugframe::LoginServiceInterface::LoginStatus loginStatus;
        quint32 sessionId;
        QString profil;
        QScopedPointer<oplink::Message> p;
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

            if (loginStatus == plugframe::LoginServiceInterface::LoginStatus::Ok)
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
                                                      oplink::SigninReplyMessage::SigninStatus::InternalErr));
                }
            }
            else
            {
                p.reset(createSigninFailedMessage(msg->identifier(),
                                                  static_cast<oplink::SigninReplyMessage::SigninStatus>(loginStatus)));
            }
        }
        else
        {
            pfErr(s_TcpBackendLogChannel) << tr("Users login service not found!");
            p.reset(createSigninFailedMessage(msg->identifier(),
                                              oplink::SigninReplyMessage::SigninStatus::InternalErr));
        }

        sendMessage(*p); //sigin reply

        if (openSession)
        {
            emit sigDelayedOpenSession(sessionId,profil);  // queued connection !
        }


    }//if (msg)
}

void TcpBackendChannelManager::processSignoutMessage(oplink::SignoutMessage *msg)
{
    if (msg)
    {
        quint32 sid{msg->sessionId()};
        closeSession(sid);
    }
}

void TcpBackendChannelManager::processDownloadConfigMessage(oplink::DownloadConfigMessage *msg)
{
    if (msg)
    {
        QScopedPointer<oplink::Message> p;
        QString configContent;
        quint32 sid{msg->sessionId()};

        configContent = confContentFromSession(sid);
        p.reset(createDownloadConfigReplyMessage(sid,configContent));
        sendMessage(*p);
    }
}

void TcpBackendChannelManager::processReadyMessage(oplink::ReadyMessage *msg)
{
    if (msg)
    {
        quint32 sid{msg->sessionId()};

        enableSession(sid);
    }
}

void TcpBackendChannelManager::processSubmitOrderMessage(oplink::SubmitOrderMessage *msg)
{
    if (msg)
    {
        quint32 sid{msg->sessionId()};
        submitOrderToSession(sid,msg->order());
    }
}

plugframe::LoginServiceInterface *TcpBackendChannelManager::loginService()
{
    TcpBackend& tcpBundle{dynamic_cast<TcpBackend&>(bundle())};

    return tcpBundle.loginService();
}

bool TcpBackendChannelManager::openSession(const quint32& sessionId,
                               const QString& profil,
                               plugframe::LoginServiceInterface *lService,
                               qint16& confId)
{
    bool ret{false};
    oplink::ObservableServiceInterface *oService{tcpBackendBundle().observableService()};
    QString fileName{lService->absoluteUserConfFileName(profil)};
    oplink::QspSubscribeSession rs;

    rs.reset(createRemoteMonitoringSession(sessionId,fileName,oService));
    m_remoteMonitoringSessions.insert(sessionId,rs);
    bool ok = connect(rs.get(),
            SIGNAL(newState(quint32,oplink::ObservableName,oplink::PropertyName,QVariant)),
            SLOT(onNewState(quint32,oplink::ObservableName,oplink::PropertyName,QVariant)));
    if (!ok)
    {
        pfErr(s_TcpBackendLogChannel) << tr("Can't connect newState signal from remote monit:oring session!");
    }
    ret = rs->open(confId);

    return ret;
}

void TcpBackendChannelManager::enableSession(const quint32 &sessionId)
{
    oplink::QspSubscribeSession session;

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
    oplink::QspSubscribeSession session;

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
    oplink::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        ret = session->confContent();
    }

    return ret;
}

void TcpBackendChannelManager::submitOrderToSession(const quint32 &sessionId, const QString &order)
{
    oplink::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->submitOrder(order);
    }
}

