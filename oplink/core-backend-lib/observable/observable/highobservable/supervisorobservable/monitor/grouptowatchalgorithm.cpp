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

oplink::GroupToWatchAlgorithm::GroupToWatchAlgorithm(oplink::SupervisorObservable& manager, QObject *parent):
    oplink::ObservableSubscriber{parent},
    m_manager{manager},
    m_group{nullptr}
{
    // move this object to the main thread
    moveToThread(QCoreApplication::instance()->thread());
}

oplink::GroupToWatchAlgorithm::~GroupToWatchAlgorithm()
{

}

void oplink::GroupToWatchAlgorithm::observableService(oplink::ObservableServiceInterface *obService)
{
    m_observableService = obService;
}

void oplink::GroupToWatchAlgorithm::subscribeToCategory(const QString &category,
                                                        oplink::GroupToWatch *myRoom)
{
    oplink::QspStateToWatchList monitoredList{myRoom->category(category)};

    for (qsizetype i = 0 ; i < monitoredList->size(); i++)
    {
        oplink::QspStateToWatch monitoredState{monitoredList->at(i)};

        m_observableService->subscribe(monitoredState->observableName(), this);
    }
}

void oplink::GroupToWatchAlgorithm::unsubscribeToCategory(const QString &category,
                                                          GroupToWatch *myRoom)
{
    oplink::QspStateToWatchList monitoredList{myRoom->category(category)};

    for (qsizetype i = 0 ; i < monitoredList->size(); i++)
    {
        oplink::QspStateToWatch monitoredState{monitoredList->at(i)};

        m_observableService->unsubscribe(monitoredState->observableName(), this);
    }
}
