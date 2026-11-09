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
#include "observablepublisherclientconnection.h"
#include "observablepublishermessagescodec.h"
#include "observablepublisher.h"
#include "observablepublisher_logchannel.h"
#include "network/channel/outputstreambuilder.h"
#include "logger/pflog.h"

ObservablePublisherClientConnection::ObservablePublisherClientConnection(plugframe::Publisher *bundle,
                                                                         plugframe::MessagesCodec *codec,
                                                                         QObject *parent):
    plugframe::ClientConnection{bundle,codec,parent}
{
    // Connect Codec for messages processing from network
    ObservablePublisherMessagesCodec *observablePublisherCodec{dynamic_cast<ObservablePublisherMessagesCodec*>(codec)};

    if (observablePublisherCodec)
    {
        // input messages
        connect(observablePublisherCodec,SIGNAL(signinMessage(QString,QString,QString,QString)),SLOT(onSigninMessage(QString,QString,QString,QString)));
        connect(observablePublisherCodec,SIGNAL(signoutMessage(quint32)),SLOT(onSignoutMessage(quint32)));
        connect(observablePublisherCodec,SIGNAL(downloadConfigMessage(quint32)),SLOT(onDownloadConfigMessage(quint32)));
        connect(observablePublisherCodec,SIGNAL(readyMessage(quint32)),SLOT(onReadyMessage(quint32)));
        connect(observablePublisherCodec,SIGNAL(submitOrderMessage(quint32,QString)),SLOT(onSubmitOrderMessage(quint32,QString)));

        // session openning
        connect(this,SIGNAL(delayedOpenSession(quint32,QString)),SLOT(onDelayedOpenSession(quint32,QString)),Qt::QueuedConnection);
    }
}

ObservablePublisherClientConnection::~ObservablePublisherClientConnection()
{
    closeAllSessions();
}

void ObservablePublisherClientConnection::onSigninMessage(QString frontendItf, QString frontendIp, QString identifier, QString password)
{
    ObservablePublisher *publisherBundle{observablePublisherBundle()};

    if (publisherBundle)
    {
        plugframe::LoginServiceInterface *loginServ{publisherBundle->loginService()};

        if (loginServ)
        {
            plugframe::LoginServiceInterface::LoginStatus loginStatus;
            bool openSession{false};
            QString profil;
            quint32 sessionId;
            plugframe::QspOutputStream outputStream;
            loginServ->login(frontendItf,
                             frontendIp,
                             identifier,
                             password,
                             loginStatus,
                             sessionId,
                             profil);
            if (loginStatus == plugframe::LoginServiceInterface::LoginStatus::Ok)
            {
                if (m_remoteMonitoringSessions.find(sessionId) == m_remoteMonitoringSessions.end())
                {
                    outputStream.reset(createEmbeddedSigninSuccessMessage(identifier,sessionId));
                    openSession = true;
                }//if (m_remoteMonitoringSessions.find(sessionId) == m_remoteMonitoringSessions.end())
                else
                {
                    pfErr(s_ObservablePublisher_LogChannel) << tr("Duplicate session Id : ") << sessionId;
                    outputStream.reset(createEmbeddedSigninFailedMessage(identifier,oplink::SigninStatus::InternalErr));
                }
            }//if (loginStatus == plugframe::LoginServiceInterface::LoginStatus::Ok)
            else
            {
                outputStream.reset(createEmbeddedSigninFailedMessage(identifier,static_cast<oplink::SigninStatus>(loginStatus)));
            }

            sendMessage(outputStream); //sigin reply

            if (openSession)
            {
                emit delayedOpenSession(sessionId,profil);  // queued connection !
            }

        }//if (loginServ)
    }//if (publisherBundle)
}

void ObservablePublisherClientConnection::onSignoutMessage(quint32 sessionId)
{
    closeSession(sessionId);
}

void ObservablePublisherClientConnection::onDownloadConfigMessage(quint32 sessionId)
{
    QString configContent{confContentFromSession(sessionId)};
    plugframe::QspOutputStream outputStream;

    outputStream.reset(createEmbeddedDownloadConfigReplyMessage(sessionId,configContent));
    sendMessage(outputStream);
}

void ObservablePublisherClientConnection::onReadyMessage(quint32 sessionId)
{
    enableSession(sessionId);
}

void ObservablePublisherClientConnection::onSubmitOrderMessage(quint32 sessionId, QString order)
{
    submitOrderToSession(sessionId,order);
}

void ObservablePublisherClientConnection::onDelayedOpenSession(quint32 sessionId, QString profil)
{
    ObservablePublisher *publisherBundle{observablePublisherBundle()};

    if (publisherBundle)
    {
        plugframe::LoginServiceInterface *loginServ{publisherBundle->loginService()};

        if (loginServ)
        {
            plugframe::QspOutputStream outputStream;
            qint16 confId;
            bool ok;

            ok = openSession(sessionId,profil,loginServ,confId);
            if (ok)
            {
                pfInfo1(s_ObservablePublisher_LogChannel) << tr("Session open : ") << sessionId;
                outputStream.reset(createEmbeddedSessionStartedMessage(sessionId,confId,profil));
            }
            else
            {
                pfErr(s_ObservablePublisher_LogChannel) << tr("Failed to open a new session for id : ") << sessionId;
                outputStream.reset(createEmbeddedSessionStartedMessage(0,0,"")); // return internal server error
            }

            sendMessage(outputStream); // session started on server

        }//if (loginServ)
    }//if (publisherBundle)
}

void ObservablePublisherClientConnection::onNewState(quint32 sessionId, oplink::ObservableName observableName, oplink::PropertyName propertyName, QVariant propertyValue)
{
    plugframe::QspOutputStream outputStream;

    outputStream.reset(createEmbeddedStateValueMessage(sessionId,observableName,propertyName,propertyValue));
    sendMessage(outputStream);
}

ObservablePublisher *ObservablePublisherClientConnection::observablePublisherBundle()
{
    return dynamic_cast<ObservablePublisher*>(bundle());
}

oplink::SubscribeSession *ObservablePublisherClientConnection::createRemoteMonitoringSession(const quint32 &sessionId,
                                                                                             const QString &fileName,
                                                                                             oplink::ObservableServiceInterface *observableService)
{
    return new oplink::SubscribeSession(sessionId,fileName,observableService);
}

bool ObservablePublisherClientConnection::openSession(const quint32 &sessionId,
                                                      const QString &profil,
                                                      plugframe::LoginServiceInterface *lService,
                                                      qint16 &confId)
{
    bool ret{false};
    oplink::ObservableServiceInterface *oService{observablePublisherBundle()->observableService()};
    QString fileName{lService->absoluteUserConfFileName(profil)};
    oplink::QspSubscribeSession rs;

    rs.reset(createRemoteMonitoringSession(sessionId,fileName,oService));
    m_remoteMonitoringSessions.insert(sessionId,rs);
    bool ok = connect(rs.get(),
                      SIGNAL(newState(quint32,oplink::ObservableName,oplink::PropertyName,QVariant)),
                      SLOT(onNewState(quint32,oplink::ObservableName,oplink::PropertyName,QVariant)));
    if (!ok)
    {
        pfErr(s_ObservablePublisher_LogChannel) << tr("Can't connect newState signal from remote monitoring session!");
    }
    ret = rs->open(confId);

    return ret;
}

void ObservablePublisherClientConnection::closeSession(const quint32 &sessionId)
{
    oplink::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->close();
        m_remoteMonitoringSessions.remove(sessionId);
    }
}

void ObservablePublisherClientConnection::closeAllSessions()
{
    QList<quint32> listKeys{m_remoteMonitoringSessions.keys()};

    for (auto i = 0; i < listKeys.size(); i++)
    {
        closeSession(listKeys.at(i));
    }
}

QString ObservablePublisherClientConnection::confContentFromSession(const quint32 &sessionId)
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

void ObservablePublisherClientConnection::enableSession(const quint32 &sessionId)
{
    oplink::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->enableMonitoring();
    }
}

void ObservablePublisherClientConnection::submitOrderToSession(const quint32 &sessionId, const QString &order)
{
    oplink::QspSubscribeSession session;

    session = m_remoteMonitoringSessions.value(sessionId);
    if (!session.isNull())
    {
        session->submitOrder(order);
    }
}

plugframe::OutputStream *ObservablePublisherClientConnection::createEmbeddedSigninSuccessMessage(const QString &identifier, const quint32 &sessionId)
{
    plugframe::OutputStreamBuilder *ret{messagesCodec()->createOutputStream(static_cast<quint16>(oplink::MessageType::SigninReply))};
    quint8 status{static_cast<quint8>(oplink::SigninStatus::Ok)};

    ret->stream() << sessionId << identifier << status;
    return ret;
}

plugframe::OutputStream *ObservablePublisherClientConnection::createEmbeddedSigninFailedMessage(const QString &identifier, const oplink::SigninStatus &status)
{
    plugframe::OutputStreamBuilder *ret{messagesCodec()->createOutputStream(static_cast<quint16>(oplink::MessageType::SigninReply))};
    quint32 sessionId{0};

    ret->stream() << sessionId << identifier << static_cast<quint8>(status);
    return ret;
}

plugframe::OutputStream *ObservablePublisherClientConnection::createEmbeddedSessionStartedMessage(const quint32 &sessionId, const qint16 &confId, const QString &profil)
{
    plugframe::OutputStreamBuilder *ret{messagesCodec()->createOutputStream(static_cast<quint16>(oplink::MessageType::SessionStarted))};

    ret->stream() << sessionId << confId << profil;
    return ret;
}

plugframe::OutputStream *ObservablePublisherClientConnection::createEmbeddedDownloadConfigReplyMessage(const quint32 &sessionId, const QString &confContent)
{
    plugframe::OutputStreamBuilder *ret{messagesCodec()->createOutputStream(static_cast<quint16>(oplink::MessageType::DownloadConfigReply))};

    ret->stream() << sessionId << confContent;
    return ret;
}

plugframe::OutputStream *ObservablePublisherClientConnection::createEmbeddedStateValueMessage(const quint32 &sessionId, const QString &observableName, const QString &propertyName, const QVariant &value)
{
    plugframe::OutputStreamBuilder *ret{messagesCodec()->createOutputStream(static_cast<quint16>(oplink::MessageType::StateValue))};

    ret->stream() << sessionId << observableName << propertyName << value;
    return ret;
}

plugframe::OutputStream *ObservablePublisherClientConnection::createEmbeddedSignoutMessage(const quint32 &sessionId)
{
    plugframe::OutputStreamBuilder *ret{messagesCodec()->createOutputStream(static_cast<quint16>(oplink::MessageType::Signout))};

    ret->stream() << sessionId;
    return ret;
}

