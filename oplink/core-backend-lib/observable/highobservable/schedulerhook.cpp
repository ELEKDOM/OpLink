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
#include "schedulerhook.h"
#include "schedulableobservable.h"
#include "scheduler/scheduler.h"

oplink::SchedulerHook::SchedulerHook(oplink::SchedulableObservable& myVe, QObject *parent)
    : QObject{parent},
    m_myVe{myVe}
{
    // the Hook qobject must be into the main thread !
    moveToThread(QCoreApplication::instance()->thread());
}

oplink::SchedulerHook::~SchedulerHook()
{

}

void oplink::SchedulerHook::setScheduler(plugframe::Scheduler *schedul)
{
    m_scheduler.reset(schedul);
    connect(m_scheduler.data(), SIGNAL(trigger(QString)), SLOT(onSchedulerEvt(QString)));
}

void oplink::SchedulerHook::initScheduler()
{
    if(!m_scheduler.isNull())
    {
        m_scheduler->init();
    }
}

void oplink::SchedulerHook::onSchedulerEvt(QString evt)
{
    m_myVe.onSchedulerEvt(evt);
}
