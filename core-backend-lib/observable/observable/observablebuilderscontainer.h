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

#ifndef OBSERVABLEBUILDERSCONTAINER_H
#define OBSERVABLEBUILDERSCONTAINER_H

#include <QHash>
#include "observable/observablenames.h"
#include "observable/observable/observablebuilder.h"
#include "olcore-backend-lib_export.h"
//#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ObservableBuildersContainer
{
public:
    using ConstIt = QHash<ObservableName, QspObservableBuilder>::const_iterator;

public:
    ObservableBuildersContainer();
    ~ObservableBuildersContainer();

public:
    bool insert(const ObservableName& name,const QspObservableBuilder& observable);
    bool find(const ObservableName& name,QspObservableBuilder& observable);
    bool contains(const ObservableName& name) const;
    ConstIt begin();
    ConstIt end();

private:
    QHash<ObservableName, QspObservableBuilder> m_observables;
};
}//namespace oplink
#endif // OBSERVABLEBUILDERSCONTAINER_H
