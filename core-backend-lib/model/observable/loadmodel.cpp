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

#include "loadmodel.h"
#include "model/observable/observablebuilderargs.h"
#include "model/observable/loadbuilderargs.h"
#include "observable/lowobservable/load.h"

oplink::LoadModel::LoadModel(const oplink::ObservableModelName &name) :
    oplink::ObservableModel{name}
{

}

oplink::LoadModel::~LoadModel()
{

}

bool oplink::LoadModel::checkBuilderArgs(oplink::QspObservableBuilderArgs builderArgs)
{
    oplink::QspLoadBuilderArgs loadArgs{builderArgs.dynamicCast<oplink::LoadBuilderArgs>()};
    return !loadArgs.isNull();
}

oplink::ObservableBuilder *oplink::LoadModel::createInstance(oplink::QspObservableBuilderArgs builderArgs)
{
    Q_UNUSED(builderArgs)

    return new oplink::Load;
}
