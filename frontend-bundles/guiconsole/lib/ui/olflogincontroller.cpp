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


#include "olflogincontroller.h"
#include "olfloginview.h"
#include "olfconsole.h"

using namespace elekdom::oplink::frontend::guiconsole;

OlfLoginController::OlfLoginController(bundle::OlfConsole& console,
                                       int maxLoginAttempts,
                                       QObject *parent):
    OlfConsoleController{console,
                         LoginPageCtrlName(),
                         QStringList{monitoringMenuName(),LoginMenuName()},
                         parent},
    m_maxLoginAttempts{maxLoginAttempts},
    m_siginAttempsNumber{0}
{
    state(State::WaitingForServer);
}

OlfLoginController::~OlfLoginController()
{

}

void OlfLoginController::connectedToServer()
{
    emit enableLogin();
    clearStatusMsg();
    state(State::WaitingForUserLogin);
    m_siginAttempsNumber = 0;
}

void OlfLoginController::sessionClosed(bool disconnectedFromServer)
{
    if (disconnectedFromServer)
    {
        emit lockLogin();
        state(State::WaitingForServer);
    }
    else
    {
        connectedToServer();
    }
}

void OlfLoginController::siginResult(bool success, const QString& ident)
{
    if (state() == State::WaitingForUserLogin && m_identifier == ident)
    {
        m_siginAttempsNumber++;
        if (!success)
        {
            if (m_siginAttempsNumber >= m_maxLoginAttempts)
            {
                statusMsg(tr("Sigin failed!"));
                emit lockLogin();
            }
            else
            {
                statusMsg(tr("Sigin failed. %1 tries left!").arg(m_maxLoginAttempts - m_siginAttempsNumber));
            }
        }
        else
        {
            state(State::UserLogged);
            statusMsg(tr("Sigin succes"));
            emit loginSuccess();
            emit userLogged();
        }
    }
}

void OlfLoginController::buildViews()
{
    OlfLoginView *view{createLoginView()};

    //specific view/controller connections
    connect(this, SIGNAL(enableLogin()), view, SLOT(enableLogin()));
    connect(this, SIGNAL(lockLogin()), view, SLOT(lockLogin()));
    connect(this, SIGNAL(loginSuccess()), view, SLOT(loginSuccess()));
    connect(this, SIGNAL(resetView()), view, SLOT(reset()));
    connect(view, SIGNAL(sigin(QString,QString)), this, SLOT(onSignin(QString,QString)));

    //kept view
    addView(view);
}

OlfLoginView *OlfLoginController::createLoginView()
{
    return new OlfLoginView;
}

void OlfLoginController::onCurrent()
{
    State curState{state()};
    switch (curState)
    {
        case State::WaitingForServer:
            statusMsg(tr("Waiting for server available"));
        break;

        case State::WaitingForUserLogin:
            statusMsg(tr("Waiting for user login"));
        break;

        case State::UserLogged:
            statusMsg(tr("User logged"));
        break;

        default:
        break;
    }
}

void OlfLoginController::onSignin(QString identifier, QString passwd)
{
    State curState{state()};

    // Log in or Log out ?
    if (curState == State::WaitingForUserLogin)
    {
        m_identifier = identifier;
        bundle().sendSigninToServer(identifier,passwd);
    }
    else if (curState == State::UserLogged)
    {
        bundle().logOut();
    }
}
