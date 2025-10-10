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


#ifndef SCHEDULERHOOK_H
#define SCHEDULERHOOK_H

#include <QObject>
#include "pfcore-lib_forward.h"
#include "olcore-backend-lib_forward.h"

using namespace elekdom::plugframe::core::scheduler;

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

class SchedulerHook : public QObject
{
    Q_OBJECT

public:
    explicit SchedulerHook(SchedulableObservable& myVe, QObject *parent = nullptr);
    ~SchedulerHook() override;

public:
    void setScheduler(Scheduler *schedul);
    void initScheduler();

private slots:
    void onSchedulerEvt(QString evt);

private:
    SchedulableObservable& m_myVe;
    QspScheduler m_scheduler;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // SCHEDULERHOOK_H
