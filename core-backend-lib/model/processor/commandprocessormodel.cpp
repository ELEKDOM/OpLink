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


#include "commandprocessormodel.h"
#include "logger/pflog.h"
#include "model/modellogchannel.h"

using namespace elekdom::oplink::core::model;

CommandProcessorModel::CommandProcessorModel(const ProcessorModelName& modelName,
                                                   const command::CommandName& commandName) :
    plugframe::core::logger::Loggable{s_ModelLogChannel},
    m_modelName{modelName},
    m_commandName{commandName}
{
    pfDebug1(logChannel()) << "->CommandProcessorModel::CommandProcessorModel, " << modelName << ", " << commandName;

    pfDebug1(logChannel()) << "<-CommandProcessorModel::CommandProcessorModel";
}

CommandProcessorModel::~CommandProcessorModel()
{

}
