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

#ifndef INFRASTRUCTURELOADEROUTS_H
#define INFRASTRUCTURELOADEROUTS_H

#include <QSharedPointer>
#include "olcore-backend-lib_export.h"
#include "abstract_infrastructure/loading/infrastructureworkerouts.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "observable/observable/observablebuilderscontainer.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT InfrastructureLoaderOuts : public InfrastructureWorkerOuts
{
public:
    InfrastructureLoaderOuts(InfrastructureName infrastructureName,
                             bool loadedFlag,
                             QspObservableBuildersContainer loadedObservables);
    ~InfrastructureLoaderOuts() override;

public:
    QspObservableBuildersContainer m_loadedObservables;
};
using QspInfrastructureLoaderOuts = QSharedPointer<InfrastructureLoaderOuts>;
}//namespace oplink
#endif // INFRASTRUCTURELOADEROUTS_H
