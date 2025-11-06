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

#include "logger/pflog.h"
#include "loader/enoceandevicebuilder.h"
#include "device/d20112eep.h"
#include "device/d2010ceep.h"
#include "device/d2010eeep.h"
#include "device/f60101eep.h"
#include "device/f60201eep.h"
#include "device/a50401eep.h"
#include "device/d50001eep.h"
#include "enoceaninfrastructurelogchannel.h"

const QString EnoceanDeviceBuilder::D20112_EEP{QStringLiteral("d20112")};
const QString EnoceanDeviceBuilder::D2010C_EEP{QStringLiteral("d2010c")};
const QString EnoceanDeviceBuilder::D2010E_EEP{QStringLiteral("d2010e")};
const QString EnoceanDeviceBuilder::F60101_EEP{QStringLiteral("f60101")};
const QString EnoceanDeviceBuilder::F60201_EEP{QStringLiteral("f60201")};
const QString EnoceanDeviceBuilder::A50401_EEP{QStringLiteral("a50401")};
const QString EnoceanDeviceBuilder::D50001_EEP{QStringLiteral("d50001")};

EnoceanDeviceBuilder::EnoceanDeviceBuilder(const oplink::QspDeviceProcessorBuilder& processorBuilder):
    oplink::DeviceBuilder{processorBuilder}
{

}

EnoceanDeviceBuilder::~EnoceanDeviceBuilder()
{

}

oplink::QspDevice EnoceanDeviceBuilder::createDevice(const oplink::DeviceId &id,
                                                     const oplink::DeviceModelName &deviceModelName,
                                                     oplink::DeviceHook &deviceHook)
{
    oplink::QspDevice ret;

    if (D20112_EEP == deviceModelName)
    {
        ret.reset(createD20112(id, deviceHook));
    }
    else if(D2010C_EEP == deviceModelName)
    {
        ret.reset(createD2010C(id, deviceHook));
    }
    else if(D2010E_EEP == deviceModelName)
    {
        ret.reset(createD2010E(id, deviceHook));
    }
    else if(F60101_EEP == deviceModelName)
    {
        ret.reset(createF60101(id, deviceHook));
    }
    else if(F60201_EEP == deviceModelName)
    {
        ret.reset(createF60201(id, deviceHook));
    }
    else if(A50401_EEP == deviceModelName)
    {
        ret.reset(createA50401(id, deviceHook));
    }
    else if(D50001_EEP == deviceModelName)
    {
        ret.reset(createD50001(id, deviceHook));
    }
    else
    {
        pfErr(s_EnoceanLogChannel) << QObject::tr("Enocean Equipment Profile: ") << deviceModelName << QObject::tr(", non implémenté");
    }

    return ret;
}

oplink::Device *EnoceanDeviceBuilder::createD20112(const oplink::DeviceId &id,
                                                   oplink::DeviceHook &deviceHook)
{
    return new D20112Eep{id, deviceHook};
}

oplink::Device *EnoceanDeviceBuilder::createD2010C(const oplink::DeviceId &id,
                                                   oplink::DeviceHook &deviceHook)
{
    return new D2010CEep{id, deviceHook};
}

oplink::Device *EnoceanDeviceBuilder::createD2010E(const oplink::DeviceId &id,
                                                   oplink::DeviceHook &deviceHook)
{
    return new D2010EEep{id, deviceHook};
}

oplink::Device *EnoceanDeviceBuilder::createF60101(const oplink::DeviceId &id,
                                                   oplink::DeviceHook &deviceHook)
{
    return new F60101Eep{id, deviceHook};
}

oplink::Device *EnoceanDeviceBuilder::createF60201(const oplink::DeviceId &id, oplink::DeviceHook &deviceHook)
{
    return new F60201Eep{id, deviceHook};
}

oplink::Device *EnoceanDeviceBuilder::createA50401(const oplink::DeviceId &id,
                                                   oplink::DeviceHook &deviceHook)
{
    return new A50401Eep{id, deviceHook};
}

oplink::Device *EnoceanDeviceBuilder::createD50001(const oplink::DeviceId &id, oplink::DeviceHook &deviceHook)
{
    return new D50001Eep{id, deviceHook};
}
