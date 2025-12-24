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

#ifndef STARTINGCLIENTSSTATE_H
#define STARTINGCLIENTSSTATE_H

#include "serverstartingstate.h"

class StartingClientsState : public ServerStartingState
{

public:
    StartingClientsState(ServerEngine& engine);
    ~StartingClientsState() override;

protected:
    void starting() override;
    void doProcessing(const plugframe::QspWorkerOuts& outs) override;
    bool test4transition() override;
    void transition() override;

private:
    int m_nbFrontendItfs;
};
#endif // STARTINGCLIENTSSTATE_H
