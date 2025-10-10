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


#include <QCoreApplication>
#include "grouptowatchalgorithm.h"
#include "grouptowatch.h"
#include "statetowatchlist.h"

using namespace elekdom::oplink::core::observable::monitoring;

GroupToWatchAlgorithm::GroupToWatchAlgorithm(SupervisorObservable& manager, QObject *parent):
    ObservableSubscriber{parent},
    m_manager{manager},
    m_group{nullptr}
{
    moveToThread(QCoreApplication::instance()->thread());
}

GroupToWatchAlgorithm::~GroupToWatchAlgorithm()
{

}

void GroupToWatchAlgorithm::initAlgorithm(engine::service::ObservableServiceInterface *observableService)
{
    m_observableService = observableService;
    initAlgo();
}

void GroupToWatchAlgorithm::subscribeToCategory(const QString &category,
                                                monitoring::GroupToWatch *myRoom,
                                                engine::service::ObservableServiceInterface *observableService)
{
    observable::monitoring::QspMonitoredStateList monitoredList{myRoom->category(category)};

    for (int i = 0 ; i < monitoredList->size(); i++)
    {
        observable::monitoring::QspMonitoredState monitoredState{monitoredList->at(i)};

        observableService->subscribe(monitoredState->observableName(), this);
    }
}

