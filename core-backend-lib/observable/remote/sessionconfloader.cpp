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


#include "sessionconfloader.h"
#include "subscribesession.h"
#include "observable/remote/observablestates.h"

using namespace elekdom::oplink::core::remote;

SessionConfLoader::SessionConfLoader(SubscribeSession &session):
    m_session{session}
{

}

SessionConfLoader::~SessionConfLoader()
{

}

void SessionConfLoader::browseBegin()
{

}

void SessionConfLoader::browseEnd()
{

}

void SessionConfLoader::beginObservableDeclaration(QString observableName, QString observableTitle, QString observableType, QString observableLocalisation)
{
    Q_UNUSED(observableTitle)
    Q_UNUSED(observableType)
    Q_UNUSED(observableLocalisation)
    m_curRemoteMonitoredDeclaration.reset(new core::remote::ObservableStates);
    m_curObservableName = observableName;
}

void SessionConfLoader::endObservableDeclaration()
{
    m_session.addRemoteMonitoredObservable(m_curObservableName,
                                           m_curPropertyNames,
                                           m_curRemoteMonitoredDeclaration);
}

void SessionConfLoader::propertyDeclaration(QString propertyName)
{
    m_curPropertyNames << propertyName;
}
