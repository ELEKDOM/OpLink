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

#ifndef SENSORMODEL_H
#define SENSORMODEL_H

#include "operationdevicemodel.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT SensorModel : public OperationDeviceModel
{
public:
    SensorModel(const ObservableModelName& name);
    ~SensorModel() override;

protected:
    bool checkBuilderArgs(QspObservableBuilderArgs builderArgs) override;
};
}//namespace oplink
#endif // SENSORMODEL_H
