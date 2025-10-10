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


#ifndef OLFCONSOLECONTROLLER_H
#define OLFCONSOLECONTROLLER_H

#include "gui/guipagecontroller.h"
#include "olfconsole_forward.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{

class OlfConsoleController : public plugframe::core::gui::GuiPageController
{
    Q_OBJECT

public:
    enum class State : quint8 {UnKnown,
                               WaitingForServer,     // Login Controller
                               WaitingForUserLogin,
                               UserLogged,
                               WaitingForUserLogged, // Monitored Observables Controller
                               WaitingForSessionStarted,
                               WaitingForConfUpdate,
                               SessionInProgress};

protected:
    static inline QString monitoringMenuName() {return tr("&Monitoring");}

public:
    OlfConsoleController(bundle::OlfConsole& console,
                         const QString& ctrlName,
                         QStringList menusNames = QStringList(),
                         QObject *parent = nullptr);
    ~OlfConsoleController() override;

public:
    State state() {return m_curState;}

protected:
    void buildViews() override;
    bundle::OlfConsole& bundle() {return m_bundle;}

protected:
    void state(State val) {m_curState = val;}

private:
    bundle::OlfConsole& m_bundle;
    State               m_curState;
};

} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFCONSOLECONTROLLER_H
