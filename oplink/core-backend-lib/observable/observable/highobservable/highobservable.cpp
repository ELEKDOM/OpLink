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

#include "highobservable.h"
#include "observable/property/propertyid.h"
#include "observable/values.h"

oplink::HighObservable::HighObservable(const plugframe::QspScheduler& scheduler):
    m_schedulerSoc{*this}
{
    m_schedulerSoc.setScheduler(scheduler);
}

oplink::HighObservable::~HighObservable()
{

}

void oplink::HighObservable::startScheduler(QString& currentEvt)
{
    m_schedulerSoc.startScheduler(currentEvt);
}

void oplink::HighObservable::stopScheduler()
{
    m_schedulerSoc.stopScheduler();
}

bool oplink::HighObservable::isOn()
{
    bool ret{true};
    QspProperty runningProperty{property(PropertyId::P_RUNNING)};

    if (!runningProperty.isNull())
    {
        ret = runningProperty->value().toBool();
    }

    return ret;
}

bool oplink::HighObservable::isPlannedMode()
{
    bool ret{false};
    QspProperty triggerModeProperty{property(PropertyId::P_TRIGGER_MODE)};

    if (!triggerModeProperty.isNull())
    {
        ret = triggerModeProperty->value().toString() == Values::TRIGGER_MODE_PLANNED;
    }

    return ret;
}
