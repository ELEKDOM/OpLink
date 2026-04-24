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

#ifndef COMMANDPROCESSORMODEL_H
#define COMMANDPROCESSORMODEL_H

#include <QSharedPointer>
#include "logger/loggable.h"
#include "model/modelnames.h"
#include "model/observable/observablebuilderargs.h"
#include "command/command-names.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT CommandProcessorModel : public plugframe::Loggable
{
public:
    CommandProcessorModel(const ProcessorModelName& modelName,
                          const CommandName& commandName);
    ~CommandProcessorModel() override;

public:
    const ProcessorModelName& modelName() {return m_modelName;}
    virtual CommandProcessor *createProcessor(Observable& parent,
                                              QspObservableBuilderArgs builderArgs) = 0;
protected:
    const CommandName& commandName() {return m_commandName;}

private:
    const ProcessorModelName   m_modelName;
    const CommandName          m_commandName;
};
using QspCommandProcessorModel = QSharedPointer<CommandProcessorModel>;
}//namespace oplink
#endif // COMMANDPROCESSORMODEL_H
