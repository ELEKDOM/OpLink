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


#include "olfconsolecontroller.h"

using namespace elekdom::oplink::frontend::guiconsole;
using namespace elekdom::plugframe::core::gui;

OlfConsoleController::OlfConsoleController(bundle::OlfConsole& console,
                                           const QString& ctrlName,
                                           QStringList menusNames,
                                           QObject *parent):
    GuiPageController{ctrlName,menusNames,parent},
    m_bundle{console},
    m_curState{State::UnKnown}
{}

OlfConsoleController::~OlfConsoleController()
{

}

void OlfConsoleController::buildViews()
{
    // No view by default
}
