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


#ifndef ENOCEANEQUIPMENTPROFILE_H
#define ENOCEANEQUIPMENTPROFILE_H

#include "abstract_infrastructure/device/device.h"
#include "enoceaninfrastructure_forward.h"

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class EnoceanEquipmentProfile : public core::infrastructure::Device
{
public:
    EnoceanEquipmentProfile(const core::infrastructure::DeviceId& id,
                            core::infrastructure::DeviceHook& deviceHook,
                            EepTelegramFormat *msgFormat);
    ~EnoceanEquipmentProfile() override;

public:
    void setEnoceanGateway(EnoceanGateway *gateway) {m_gateway = gateway;}
    void sendEepCommand(QspEepCommandFormat commandFormat);
    void processTelegram(QspEsp3Packet& packet);

protected:
    const QspEepTelegramFormat& msgFormat() {return m_msgFormat;}
    virtual bool processTelegram() = 0;

private:
    QspEepTelegramFormat m_msgFormat;
    EnoceanGateway      *m_gateway;
};

}//namespace bundleTemplate
}//namespace oplink
}//namespace enocean

#endif // ENOCEANEQUIPMENTPROFILE_H
