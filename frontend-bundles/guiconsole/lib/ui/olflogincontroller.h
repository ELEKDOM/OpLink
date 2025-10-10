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


#ifndef OLFLOGINCONTROLLER_H
#define OLFLOGINCONTROLLER_H

#include "olfconsolecontroller.h"
#include "olfconsole_forward.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{

class OlfLoginController : public OlfConsoleController
{
    Q_OBJECT

private:
    static inline QString LoginMenuName() {return tr("&Server connection");}
    static inline QString LoginPageCtrlName() {return QStringLiteral("Login");}   

public:
    OlfLoginController(bundle::OlfConsole& console,
                       int maxLoginAttempts,
                       QObject *parent = nullptr);
    ~OlfLoginController() override;

public:
    void connectedToServer();
    void sessionClosed(bool disconnectedFromServer);
    void siginResult(bool success, const QString& ident);

protected:
    void buildViews() override;
    OlfLoginView *createLoginView();
    void onCurrent() override;

signals:
    void enableLogin();
    void lockLogin();
    void loginSuccess();
    void resetView();
    void userLogged();

private slots:
    void onSignin(QString identifier, QString passwd);

private:
    int     m_maxLoginAttempts;
    int     m_siginAttempsNumber;
    QString m_identifier;
};

} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFLOGINCONTROLLER_H
