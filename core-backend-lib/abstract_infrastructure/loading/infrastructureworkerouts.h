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


#ifndef INFRASTRUCTUREWORKEROUTS_H
#define INFRASTRUCTUREWORKEROUTS_H

#include "olcore-backend-lib_export.h"
#include "worker/workerouts.h"
#include "abstract_infrastructure/infrastructure-names.h"

using namespace elekdom::plugframe::core;

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{

class OLCORE_BACKEND_LIB_EXPORT InfrastructureWorkerOuts : public worker::WorkerOuts
{
public:
    InfrastructureName m_infrastructureName;

public:
    InfrastructureWorkerOuts(InfrastructureName infrastructureName,
                                bool retFlag);
    ~InfrastructureWorkerOuts() override;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // INFRASTRUCTUREWORKEROUTS_H
