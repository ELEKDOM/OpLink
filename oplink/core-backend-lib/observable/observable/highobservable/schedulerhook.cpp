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
#include "highobservable.h"
#include "scheduler/scheduler.h"

oplink::SchedulerHook::SchedulerHook(oplink::HighObservable& myVe, QObject *parent)
    : QObject{parent},
    m_myVe{myVe}
{
    // move this object to the main thread
    moveToThread(QCoreApplication::instance()->thread());
}

oplink::SchedulerHook::~SchedulerHook()
{

}

void oplink::SchedulerHook::setScheduler(const plugframe::QspScheduler& schedul)
{
    m_scheduler = schedul;
    connect(m_scheduler.data(), SIGNAL(trigger(QString)), SLOT(onSchedulerEvt(QString)));
    connect(m_scheduler.data(), SIGNAL(dailySequencerIndex(int)), SLOT(onDailySequencerIndex(int)));
    connect(m_scheduler.data(), SIGNAL(dailySequencer(QString)), SLOT(onDailySequencer(QString)));
    connect(m_scheduler.data(), SIGNAL(weeklySequencer(QString)), SLOT(onWeeklySequencer(QString)));
}

void oplink::SchedulerHook::startScheduler(QString& currentEvt)
{
    currentEvt = "";
    if(!m_scheduler.isNull())
    {
        m_scheduler->start(currentEvt);
    }
}

void oplink::SchedulerHook::stopScheduler()
{
    if(!m_scheduler.isNull())
    {
        m_scheduler->stop();
    }
}

void oplink::SchedulerHook::onSchedulerEvt(QString evt)
{
    m_myVe.onSchedulerEvt(evt);
}

void oplink::SchedulerHook::onDailySequencerIndex(int idx)
{
    m_myVe.onDailySequencerIndex(idx);
}

void oplink::SchedulerHook::onWeeklySequencer(QString name)
{
    m_myVe.onWeeklySequencer(name);
}

void oplink::SchedulerHook::onDailySequencer(QString name)
{
    m_myVe.onDailySequencer(name);
}
