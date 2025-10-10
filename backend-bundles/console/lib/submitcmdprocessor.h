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


#ifndef SUBMITCMDPROCESSOR_H
#define SUBMITCMDPROCESSOR_H

#include "olcmdprocessor.h"

namespace elekdom
{
namespace oplink
{
namespace console
{
namespace cmd
{

class SubmitCmdProcessor : public OlCmdProcessor
{
public:
    SubmitCmdProcessor(const QString& logChannel,
                       bundle::OlConsole& console);
    ~SubmitCmdProcessor() override;

protected:
    bool exec(const RawCmd& cmd) override;
};

} //namespace cmd
} //namespace console
} //namespace gac
} //namespace elekdom

#endif // SUBMITCMDPROCESSOR_H
