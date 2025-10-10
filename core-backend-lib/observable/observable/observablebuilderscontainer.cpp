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


#include "observablebuilderscontainer.h"
#include "observable/observable/observablebuilder.h"

using namespace elekdom::oplink::core::observable;

ObservableBuildersContainer::ObservableBuildersContainer()
{

}

ObservableBuildersContainer::~ObservableBuildersContainer()
{
    m_observables.clear();
}

bool ObservableBuildersContainer::insert(const ObservableName &name, const QspObservableBuilder &observable)
{
    bool ret{!m_observables.contains(name)};

    if (ret)
    {
        m_observables.insert(name, observable);
    }

    return ret;
}

bool ObservableBuildersContainer::find(const ObservableName &name, QspObservableBuilder &observable)
{
    bool ret{m_observables.contains(name)};

    if (ret)
    {
        observable = m_observables.value(name);
    }

    return ret;
}

bool ObservableBuildersContainer::contains(const ObservableName &name) const
{
    return m_observables.contains(name);
}

ObservableBuildersContainer::ConstIt ObservableBuildersContainer::begin()
{
    return m_observables.constBegin();
}

ObservableBuildersContainer::ConstIt ObservableBuildersContainer::end()
{
    return m_observables.constEnd();
}
