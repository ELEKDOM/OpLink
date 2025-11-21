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

#ifndef ACTUATORMODEL_H
#define ACTUATORMODEL_H

#include "model/modelnames.h"
#include "model/observable/operationdevicemodel.h"
#include "observable/observable/observablebuilderscontainer.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ActuatorModel : public OperationDeviceModel
{
public:
    ActuatorModel(const ObservableModelName& name);
    ~ActuatorModel() override;

protected:
    bool checkBuilderArgs(QspObservableBuilderArgs builderArgs) override;
    bool buildProperties(QspObservableBuilder observableBuilder,
                         QspObservableBuilderArgs builderArgs) override;
    bool bindOutputs(QspObservableBuilder actuatorBuilder,
                     const ActuatorOutputsBinding& actuatorOutputsBinding,
                     const QspObservableBuildersContainer& loadedObservables);
};
}//namespace oplink
#endif // ACTUATORMODEL_H
