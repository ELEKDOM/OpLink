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


#include "loadcommandprocessormodel.h"
#include "model/observable/observablebuilderargs.h"
#include "observable/processor/loadcommandprocessor.h"

using namespace elekdom::oplink::core::model;
using namespace elekdom::oplink::core;

LoadCommandProcessorModel::LoadCommandProcessorModel(const ProcessorModelName& modelName,
                                                           const command::CommandName& commandName):
    LowCommandProcessorModel{modelName, commandName}
{

}

LoadCommandProcessorModel::~LoadCommandProcessorModel()
{

}

observable::CommandProcessor *LoadCommandProcessorModel::createProcessor(const observable::Observable& parent,
                                                                               QspObservableBuilderArgs builderArgs)
{
    Q_UNUSED(builderArgs)
    return new observable::LoadCommandProcessor{parent, commandName()};
}
