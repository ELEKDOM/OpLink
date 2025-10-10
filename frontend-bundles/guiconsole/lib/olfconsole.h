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


#ifndef OLFCONSOLE_H
#define OLFCONSOLE_H

#include "guiconsole.h"
#include "service-int/frontendcontrolserviceinterface.h"
#include "service-int/frontendclientside.h"
#include "olfconsole_forward.h"
#include "olcore-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{
namespace bundle
{

class OlfConsole : public plugframe::guiconsole::bundle::GuiConsole,
                   public plugframe::frontend::FrontendClientSide
{

public:
    OlfConsole();
    ~OlfConsole() override;

public: // for login ctrl
    void sendSigninToServer(QString identifier, QString passwd);
    void logOut();

public: // for monitored observables controller
    void sendDownloadConfToServer();
    void sendReadyToServer();
    void sendExecCmdToServer(QString cmd);

protected:
    plugframe::core::bundle::BundleFactory* createFactory() override;
    void _start(plugframe::core::bundle::QspBundleContext bundleContext) override;
    void buildControllerViews(plugframe::guidisplay::service::GuiBuilderServiceInterface *builderGuiServiceItf) override;
    QString guiTitle() override;

protected: // client side
    void connectedToServer() override;
    void disconnectedFromServer() override;
    void messageFromServer(plugframe::core::tcp::TcpChannelMessage *msg) override;

protected: // messages to server
    core::tcp::SigninMessage *createSigninMessage(QString identifier,
                                                  QString password);
    core::tcp::SignoutMessage *createSignoutMessage();
    core::tcp::DownloadConfigMessage *createDownLoadConfigMessage();
    core::tcp::ReadyMessage *createReadyMessage();
    core::tcp::SubmitOrderMessage *createSubmitOrderMessage(QString order);

private: // messages from server
    void processSiginReplyMessage(core::tcp::SigninReplyMessage* msg);
    void processSignoutMessage(core::tcp::SignoutMessage* msg);
    void processSessionStartedMessage(core::tcp::SessionStartedMessage* msg);
    void processDownloadConfigReplyMessage(core::tcp::DownloadConfigReplyMessage* msg);
    void processStateValueMessage(core::tcp::StateValueMessage* msg);

private:
    void readIniFile(QString& serverIpv4,
                     quint16& serverPort,
                     int& maxLoginAttempts,
                     PageViewLayout& monitoringViewLayout);
    void connectToServer();
    QString cryptPassword(QString& password);
    void closeSession(bool disconnectedFromServer);

private:
    plugframe::frontend::service::FrontendControlServiceInterface *m_frontendTcpService;
    QspOlfLoginController m_loginCtrl;
    QspOlfMonitoredObservablesController m_monitoredObservablesCtrl;
    QString m_frontendIp;
    QString m_serverIpv4;
    quint16 m_serverPort;
};

} //namespace bundle
} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFCONSOLE_H
