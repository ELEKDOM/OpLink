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


#ifndef SCHEDULABLEOBSERVABLE_H
#define SCHEDULABLEOBSERVABLE_H

#include "pfcore-lib_forward.h"
#include "observable/highobservable/supervisorobservable.h"
#include "schedulerhook.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class OLCORE_BACKEND_LIB_EXPORT SchedulableObservable : public SupervisorObservable
{
protected:
    static QString onMode() {return QStringLiteral("on");}
    static QString offMode() {return QStringLiteral("off");}
    static QString manualMode() {return QStringLiteral("manual");}
    static QString scheduledMode() {return QStringLiteral("scheduled");}
    static QString manualDerogatedMode() {return QStringLiteral("manual(derogated)");}
    static QString scheduledDerogatedMode() {return QStringLiteral("scheduled(derogated)");}

public:
    SchedulableObservable();
    ~SchedulableObservable() override;

public:
    void setScheduler(plugframe::core::scheduler::Scheduler *schedul);
    virtual void onSchedulerEvt(QString evt) = 0;

protected:
    void initScheduler() override; // Scheduler's timers must be initialized into the main thread !
    bool isActivated();
    void mode(const QString &val);
    const QString mode();

private:
    SchedulerHook m_schedulerSoc;

};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // SCHEDULABLEOBSERVABLE_H
