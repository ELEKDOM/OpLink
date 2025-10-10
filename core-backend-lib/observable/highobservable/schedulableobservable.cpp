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


#include <QVariant>
#include "schedulableobservable.h"
#include "observable/property/propertyid.h"
#include "observable/property/property.h"

using namespace elekdom::oplink::core::observable;

SchedulableObservable::SchedulableObservable():
    m_schedulerSoc{*this}
{}

SchedulableObservable::~SchedulableObservable()
{

}

void SchedulableObservable::setScheduler(plugframe::core::scheduler::Scheduler *schedul)
{
    m_schedulerSoc.setScheduler(schedul);
}

void SchedulableObservable::initScheduler()
{
    // initialization depends on the mode value
    QString modeValStr{mode()};
    if (scheduledMode() == modeValStr || scheduledDerogatedMode() == modeValStr)
    {
        m_schedulerSoc.initScheduler();
    }
}

///
/// \brief SchedulableObservable::isActivated
/// \return true if the manager is activated
///
bool SchedulableObservable::isActivated()
{
    bool ret{false};
    QString veMode{mode()};

    ret = veMode != offMode();
    return ret;
}

void SchedulableObservable::mode(const QString &val)
{
    observable::QspProperty prop{property(observable::PropertyId::P_MODE)};
    QVariant v(val);

    prop->changeValue(v);
}

const QString SchedulableObservable::mode()
{
    QString ret;

    observable::QspProperty prop{property(observable::PropertyId::P_MODE)};
    ret = prop->value().toString();
    return ret;
}
