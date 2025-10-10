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


#ifndef OPERATIONDEVICEMODEL_H
#define OPERATIONDEVICEMODEL_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "model/modelnames.h"
#include "model/observable/observablemodel.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT OperationDeviceModel : public ObservableModel
{
public:
    OperationDeviceModel(const ObservableModelName& name);
    ~OperationDeviceModel() override;

protected:
    observable::ObservableBuilder *createInstance(QspObservableBuilderArgs builderArgs) override;
    void postBuild(observable::QspObservableBuilder observableBuilder,
                   QspObservableBuilderArgs builderArgs) override;
    virtual observable::ObservableBuilder *createObservable();
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OPERATIONDEVICEMODEL_H
