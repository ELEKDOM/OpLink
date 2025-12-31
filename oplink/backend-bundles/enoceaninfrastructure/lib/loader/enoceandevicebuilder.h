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

#ifndef ENOCEANDEVICEBUILDER_H
#define ENOCEANDEVICEBUILDER_H

#include <QString>
#include "abstract_infrastructure/loading/devicebuilder.h"
#include "abstract_infrastructure/infrastructure-names.h"

class EnoceanDeviceBuilder : public oplink::DeviceBuilder
{
public:
    static const QString D20112_EEP;
    static const QString D2010C_EEP;
    static const QString D2010E_EEP;
    static const QString F60101_EEP;
    static const QString F60201_EEP;
    static const QString A50401_EEP;
    static const QString D50001_EEP;

public:
    EnoceanDeviceBuilder(const oplink::QspDeviceProcessorBuilder& processorBuilder);
    ~EnoceanDeviceBuilder() override;

protected:
    oplink::QspDevice createDevice(const oplink::DeviceId& id,
                                   const oplink::DeviceModelName& deviceModelName,
                                   oplink::DeviceHook& deviceHook) override;
    virtual oplink::Device *createD20112(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
    virtual oplink::Device *createD2010C(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
    virtual oplink::Device *createD2010E(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
    virtual oplink::Device *createF60101(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
    virtual oplink::Device *createF60201(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
    virtual oplink::Device *createA50401(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
    virtual oplink::Device *createD50001(const oplink::DeviceId& id,
                                         oplink::DeviceHook& deviceHook);
};

#endif // ENOCEANDEVICEBUILDER_H
