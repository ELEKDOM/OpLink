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

#include <QSettings>
#include <QScopedPointer>
#include <QCryptographicHash>
#include "olfconsole.h"
#include "olfconsolefactory.h"
#include "bundle/bundlecontext.h"
#include "ui/olflogincontroller.h"
#include "ui/olfmonitoredobservablescontroller.h"
#include "network_tcp/messagetype.h"
#include "network_tcp/signinmessage.h"
#include "network_tcp/signinreplymessage.h"
#include "network_tcp/signoutmessage.h"
#include "network_tcp/sessionstartedmessage.h"
#include "network_tcp/downloadconfigmessage.h"
#include "network_tcp/readymessage.h"
#include "network_tcp/downloadconfigreplymessage.h"
#include "network_tcp/statevaluemessage.h"
#include "network_tcp/submitordermessage.h"
#include "logger/pflog.h"

OlfConsole::OlfConsole():
    m_frontendTcpService{nullptr}
{

}

OlfConsole::~OlfConsole()
{

}

void OlfConsole::sendSigninToServer(QString identifier, QString passwd)
{
    QScopedPointer<oplink::Message> msg;
    QString cryptedPwd;

    // crypt
    cryptedPwd = cryptPassword(passwd);

    // message for server
    msg.reset(createSigninMessage(identifier,cryptedPwd));

    // send message to server
    m_frontendTcpService->sendMessageToServer(*msg);
}

void OlfConsole::logOut()
{
    QScopedPointer<oplink::Message> msg;

    // message for server
    msg.reset(createSignoutMessage());

    // send message to server
    m_frontendTcpService->sendMessageToServer(*msg);

    // local log out
    closeSession(false);
}

void OlfConsole::sendDownloadConfToServer()
{
    QScopedPointer<oplink::Message> msg;

    // message for server
    msg.reset(createDownLoadConfigMessage());

    // send message to server
    m_frontendTcpService->sendMessageToServer(*msg);
}

void OlfConsole::sendReadyToServer()
{
    QScopedPointer<oplink::Message> msg;

    // message for server
    msg.reset(createReadyMessage());

    // send message to server
    m_frontendTcpService->sendMessageToServer(*msg);
}

void OlfConsole::sendExecCmdToServer(QString cmd)
{
    QScopedPointer<oplink::Message> msg;

    // message for server
    msg.reset(createSubmitOrderMessage(cmd));

    // send message to server
    m_frontendTcpService->sendMessageToServer(*msg);
}

plugframe::BundleFactory *OlfConsole::createFactory()
{
    return new OlfConsoleFactory;
}

void OlfConsole::_start(plugframe::QspBundleContext bundleContext)
{
    GuiConsole::_start(bundleContext);
    connectToServer();
}

void OlfConsole::buildControllerViews(plugframe::GuiBuilderServiceInterface *builderGuiServiceItf)
{
    OlfConsoleFactory &factory{dynamic_cast<OlfConsoleFactory&>(getFactory())};
    plugframe::QspGuiPageController qspCtrl;
    int maxLoginAttempts;
    PageViewLayout monitoringViewLayout;

    readIniFile(m_serverIpv4,m_serverPort,maxLoginAttempts,monitoringViewLayout);

    m_loginCtrl.reset(factory.createOlfLoginController(*this,maxLoginAttempts));
    m_monitoredObservablesCtrl.reset(factory.createOlfMonitoredObservablesController(*this,monitoringViewLayout));

    qspCtrl = m_monitoredObservablesCtrl.dynamicCast<plugframe::GuiPageController>();
    qspCtrl->buildViews();
    builderGuiServiceItf->addGuiController(qspCtrl);

    qspCtrl = m_loginCtrl.dynamicCast<plugframe::GuiPageController>();
    qspCtrl->buildViews();
    builderGuiServiceItf->addGuiController(qspCtrl);
    qspCtrl->currentCtrl();

    QObject::connect(m_loginCtrl.get(),SIGNAL(userLogged()),m_monitoredObservablesCtrl.get(),SLOT(onUserLogged()));
}

QString OlfConsole::guiTitle()
{
    return QStringLiteral("OpLink");
}

void OlfConsole::connectedToServer()
{
    m_loginCtrl->connectedToServer();
}

void OlfConsole::disconnectedFromServer()
{
    closeSession(true);
}

void OlfConsole::messageFromServer(plugframe::TcpChannelMessage *msg)
{
    if (msg)
    {
        quint16 msgType{msg->msgType()};

        // message types accepted from trhe server
        switch(msgType)
        {
            case static_cast<quint16>(oplink::MessageType::SiginReply) :
                if (m_loginCtrl->state() == OlfConsoleController::State::WaitingForUserLogin)
                {
                    processSiginReplyMessage(dynamic_cast<oplink::SigninReplyMessage*>(msg));
                }
                else
                {
                    pfWarning1(getLogBundleName()) << QObject::tr("unexpected SiginReply message for controller state");
                }
            break;

            case static_cast<quint16>(oplink::MessageType::Signout) :
                if (m_loginCtrl->state() == OlfConsoleController::State::UserLogged)
                {
                    processSignoutMessage(dynamic_cast<oplink::SignoutMessage*>(msg));
                }
                else
                {
                    pfWarning1(getLogBundleName()) << QObject::tr("unexpected Signout message for controller state");
                }
            break;

            case static_cast<quint16>(oplink::MessageType::SessionStarted) :
                if (m_monitoredObservablesCtrl->state() == OlfConsoleController::State::WaitingForSessionStarted)
                {
                    processSessionStartedMessage(dynamic_cast<oplink::SessionStartedMessage*>(msg));
                }
            break;

            case static_cast<quint16>(oplink::MessageType::DownloadConfigReply) :
                if (m_monitoredObservablesCtrl->state() == OlfConsoleController::State::WaitingForConfUpdate)
                {
                    processDownloadConfigReplyMessage(dynamic_cast<oplink::DownloadConfigReplyMessage*>(msg));
                }
            break;

            case static_cast<quint16>(oplink::MessageType::StateValue) :
                if (m_monitoredObservablesCtrl->state() == OlfConsoleController::State::SessionInProgress)
                {
                    processStateValueMessage(dynamic_cast<oplink::StateValueMessage*>(msg));
                }
            break;

            default:
                pfErr(getLogBundleName()) << QObject::tr("Unknown input message type : ") << msgType;
        }
    }
}

oplink::SigninMessage *OlfConsole::createSigninMessage(QString identifier, QString password)
{
    return new oplink::SigninMessage(QStringLiteral("GuiQtDesktop"),
                                     m_frontendIp,
                                     identifier,
                                     password);
}

oplink::SignoutMessage *OlfConsole::createSignoutMessage()
{
    return new oplink::SignoutMessage(m_monitoredObservablesCtrl->sessionId());
}

oplink::DownloadConfigMessage *OlfConsole::createDownLoadConfigMessage()
{
    return new oplink::DownloadConfigMessage(m_monitoredObservablesCtrl->sessionId());
}

oplink::ReadyMessage *OlfConsole::createReadyMessage()
{
    return new oplink::ReadyMessage(m_monitoredObservablesCtrl->sessionId());
}

oplink::SubmitOrderMessage *OlfConsole::createSubmitOrderMessage(QString order)
{
    return new oplink::SubmitOrderMessage(m_monitoredObservablesCtrl->sessionId(),order);
}

void OlfConsole::processSiginReplyMessage(oplink::SigninReplyMessage *msg)
{
    bool ok;

    ok = msg->status() == oplink::SigninReplyMessage::SigninStatus::Ok;
    m_loginCtrl->siginResult(ok,msg->identifier());
}

void OlfConsole::processSignoutMessage(oplink::SignoutMessage *msg)
{
    Q_UNUSED(msg)
    closeSession(false);
}

void OlfConsole::processSessionStartedMessage(oplink::SessionStartedMessage *msg)
{
    pfInfo1(getLogBundleName()) << QObject::tr("session started on server. SessionId = ") << msg->sessionId() << ", ConfId = " << msg->confId() << ", Profil = " << msg->profile();
    m_monitoredObservablesCtrl->sessionStartedOnServer(msg->sessionId(),
                                                       msg->profile(),
                                                       msg->confId());
}

void OlfConsole::processDownloadConfigReplyMessage(oplink::DownloadConfigReplyMessage *msg)
{
    pfInfo1(getLogBundleName()) << QObject::tr("Conf downloaded from server");
    m_monitoredObservablesCtrl->confDownloadedFromServer(msg->sessionId(),
                                                         msg->xmlConfig());
}

void OlfConsole::processStateValueMessage(oplink::StateValueMessage *msg)
{
    pfDebug4(getLogBundleName()) << QObject::tr("New observable state from server : ") << msg->sessionId() << "," << msg->observableName() << "," << msg->propertyName() << "," << msg->value();
    m_monitoredObservablesCtrl->newObservableStateFromServer(msg->sessionId(),
                                                             msg->observableName(),
                                                             msg->propertyName(),
                                                             msg->value());
}

void OlfConsole::readIniFile(QString& serverIpv4,
                             quint16& serverPort,
                             int &maxLoginAttempts,
                             PageViewLayout& monitoringViewLayout)
{
    QString confPath{getConfPath()};
    QSettings consoleSettings{confPath,QSettings::IniFormat};

    pfDebug5(getLogBundleName()) << QObject::tr("ini file : ") << confPath;

    consoleSettings.beginGroup("Server");
    serverIpv4 = consoleSettings.value("ipv4").toString();
    serverPort = consoleSettings.value("port").toUInt();
    consoleSettings.endGroup();

    consoleSettings.beginGroup("Login");
    maxLoginAttempts = consoleSettings.value("maxattempt",2).toUInt();
    consoleSettings.endGroup();

    monitoringViewLayout = PageViewLayout::LocalisationListLayout;
    consoleSettings.beginGroup("MonitoringView");
    QString val = consoleSettings.value("layout").toString();
    consoleSettings.endGroup();
    if (val == "Type")
    {
        monitoringViewLayout = PageViewLayout::TypeListLayout;
    }
}

void OlfConsole::connectToServer()
{
    m_frontendTcpService = bundleContext()->getService<plugframe::FrontendControlServiceInterface>(plugframe::FrontendControlServiceInterface::serviceName());
    if (m_frontendTcpService)
    {
        m_frontendTcpService->connectToHost(this,m_serverIpv4,m_serverPort);
    }
    else
    {
        pfDebug6(getLogBundleName()) << QObject::tr("No Tcp service available !");
    }
}

QString OlfConsole::cryptPassword(QString &password)
{
    QByteArray bytePasswd(password.toUtf8());
    QByteArray hash_Keccak_256;
    QString ret;

    hash_Keccak_256 = QCryptographicHash::hash(bytePasswd, QCryptographicHash::Keccak_256).toHex(':');
    ret = QString(hash_Keccak_256);

    return ret;
}

void OlfConsole::closeSession(bool disconnectedFromServer)
{
    plugframe::GuiBuilderServiceInterface *builderGuiServiceItf{bundleContext()->getService<plugframe::GuiBuilderServiceInterface>(plugframe::GuiBuilderServiceInterface::serviceName())};
    plugframe::QspGuiPageController qspCtrl;

    // update GUI
    qspCtrl = m_monitoredObservablesCtrl.dynamicCast<plugframe::GuiPageController>();
    builderGuiServiceItf->removeAllPages(qspCtrl);

    // update console
    m_monitoredObservablesCtrl->closeSession();
    m_loginCtrl->sessionClosed(disconnectedFromServer);
    m_loginCtrl->currentCtrl();
    if (disconnectedFromServer)
    {
        connectToServer();
    }
}

