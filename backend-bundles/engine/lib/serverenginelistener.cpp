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

#include "logger/pflog.h"
#include "serverenginelistener.h"
#include "serverengine.h"

ServerEngineListener::ServerEngineListener(plugframe::Bundle &bundle, QObject *parent):
    plugframe::BundleListener4fws{bundle, parent}
{

}

ServerEngineListener::~ServerEngineListener()
{

}

void ServerEngineListener::onFrameworkStartedEvent(plugframe::FrameworkStartedEvent *evt)
{
    pfDebug3(getLogBundleName()) << "->GacServerEngineListener::onFrameworkStartedEvent";
    Q_UNUSED(evt)
    ServerEngine& engineBundle{dynamic_cast<ServerEngine&>(getBundle())};

    engineBundle.startEngine();
    pfDebug3(getLogBundleName()) << "<-GacServerEngineListener::onFrameworkStartedEvent";
}
