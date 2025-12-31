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
#include "ui/olflogincontroller.h"
#include "ui/olfmonitoredobservablescontroller.h"
#include "olfconsole_forward.h"
#include "olcore-lib_forward.h"

class OlfConsole : public GuiConsole,
                   public plugframe::FrontendClientSide
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
    plugframe::BundleFactory* createFactory() override;
    void _start(plugframe::QspBundleContext bundleContext) override;
    void buildControllerViews(plugframe::GuiBuilderServiceInterface *builderGuiServiceItf) override;
    QString guiTitle() override;

protected: // client side
    void connectedToServer() override;
    void disconnectedFromServer() override;
    void messageFromServer(plugframe::TcpChannelMessage *msg) override;

protected: // messages to server
    oplink::SigninMessage *createSigninMessage(QString identifier,
                                               QString password);
    oplink::SignoutMessage *createSignoutMessage();
    oplink::DownloadConfigMessage *createDownLoadConfigMessage();
    oplink::ReadyMessage *createReadyMessage();
    oplink::SubmitOrderMessage *createSubmitOrderMessage(QString order);

private: // messages from server
    void processSiginReplyMessage(oplink::SigninReplyMessage* msg);
    void processSignoutMessage(oplink::SignoutMessage* msg);
    void processSessionStartedMessage(oplink::SessionStartedMessage* msg);
    void processDownloadConfigReplyMessage(oplink::DownloadConfigReplyMessage* msg);
    void processStateValueMessage(oplink::StateValueMessage* msg);

private:
    void readIniFile(QString& serverIpv4,
                     quint16& serverPort,
                     int& maxLoginAttempts,
                     PageViewLayout& monitoringViewLayout);
    void connectToServer();
    QString cryptPassword(QString& password);
    void closeSession(bool disconnectedFromServer);

private:
    plugframe::FrontendControlServiceInterface *m_frontendTcpService;
    QspOlfLoginController m_loginCtrl;
    QspOlfMonitoredObservablesController m_monitoredObservablesCtrl;
    QString m_frontendIp;
    QString m_serverIpv4;
    quint16 m_serverPort;
};

#endif // OLFCONSOLE_H
