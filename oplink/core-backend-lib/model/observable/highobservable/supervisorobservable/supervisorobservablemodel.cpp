// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#include "supervisorobservablemodel.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/statetowatch.h"
#include "model/observable/highobservable/supervisorobservable/supervisorobservablebuilderargs.h"

oplink::SupervisorObservableModel::SupervisorObservableModel(const ObservableModelName &name):
    HighObservableModel{name}
{

}

oplink::SupervisorObservableModel::~SupervisorObservableModel()
{

}

oplink::StateToWatch *oplink::SupervisorObservableModel::createStateToWatch(const ObservableName &observableName,
                                                                            const PropertyName &propertyName,
                                                                            const QspObservableBuilderArgs& builderArgs)
{
    StateToWatch *ret{nullptr};
    const QspSupervisorObservableBuilderArgs& supBuilderArgs{builderArgs.dynamicCast<SupervisorObservableBuilderArgs>()};
    oplink::QspProperty property;

    property = (supBuilderArgs->m_observableService)->property(observableName,propertyName);
    if (!property.isNull())
    {
        ret = new oplink::StateToWatch(property);
    }

    return ret;
}
