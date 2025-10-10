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


#ifndef ENOCEANCOMMANDPROCESSOR_H
#define ENOCEANCOMMANDPROCESSOR_H

#include "abstract_infrastructure/device/devicecommandprocessor.h"
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class EnoceanCommandProcessor : public core::infrastructure::DeviceCommandProcessor
{
public:
    EnoceanCommandProcessor(const core::infrastructure::QspDevice& device,
                            EepCommandFormat *sentCommandFormat);

    ~EnoceanCommandProcessor() override;

protected:
    QspEepCommandFormat& sentCommandFormat() {return m_sentCommandFormat;}
    void processDeviceCmd(core::command::QspCommand order) override;
    virtual bool completePacket(core::command::QspCommand order) = 0;

private:
    void sendPacket();

private:
    QspEepCommandFormat m_sentCommandFormat;
};

}//namespace bundleTemplate
}//namespace hac
}//namespace enocean

#endif // ENOCEANCOMMANDPROCESSOR_H
