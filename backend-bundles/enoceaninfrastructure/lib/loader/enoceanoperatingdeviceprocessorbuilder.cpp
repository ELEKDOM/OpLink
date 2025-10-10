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
#include "command/command-names.h"
#include "abstract_infrastructure/device/device.h"
#include "loader/enoceanoperatingdeviceprocessorbuilder.h"
#include "loader/enoceandevicebuilder.h"
#include "enoceaninfrastructurelogchannel.h"
#include "commandprocessor/D2/d201setoutput.h"
#include "commandprocessor/D2/d201statusquery.h"
#include "commandprocessor/D2/d201setpilotwiremode.h"
#include "commandprocessor/D2/d201pilotwiremodequery.h"
#include "commandprocessor/D2/d201measurementenergyquery.h"
#include "commandprocessor/D2/d201measurementpowerquery.h"

using namespace elekdom::oplink::enocean;

EnoceanOperatingDeviceProcessorBuilder::EnoceanOperatingDeviceProcessorBuilder()
{

}

EnoceanOperatingDeviceProcessorBuilder::~EnoceanOperatingDeviceProcessorBuilder()
{

}

infrastructure::DeviceCommandProcessor *EnoceanOperatingDeviceProcessorBuilder::createDeviceProcessor(const command::CommandName &commandName,
                                                                                                         const infrastructure::DeviceModelName &deviceModelName,
                                                                                                         const infrastructure::QspDevice &device)
{
    infrastructure::DeviceCommandProcessor *ret{nullptr};

    if (EnoceanDeviceBuilder::D20112_EEP == deviceModelName)
    {
        if ( core::command::CommandNames::SYNCHRONIZE == commandName)
        {
            ret = createSynchronizeD20112processor(device);
        }
        else if (core::command::CommandNames::SET == commandName)
        {
            ret = createSetD20112processor(device);
        }
    }
    else if(EnoceanDeviceBuilder::D2010C_EEP == deviceModelName)
    {
        if ( core::command::CommandNames::SYNCHRONIZE == commandName)
        {
            ret = createSynchronizeD2010Cprocessor(device);
        }
        else if (core::command::CommandNames::SET == commandName)
        {
            ret = createSetD2010Cprocessor(device);
        }
        else if (core::command::CommandNames::ENERGY == commandName)
        {
            ret = createEnergyD2010Cprocessor(device);
        }
        else if (core::command::CommandNames::POWER == commandName)
        {
            ret = createPowerD2010Cprocessor(device);
        }
    }
    else if(EnoceanDeviceBuilder::D2010E_EEP == deviceModelName)
    {
        if ( core::command::CommandNames::SYNCHRONIZE == commandName)
        {
            ret = createSynchronizeD2010Eprocessor(device);
        }
        else if (core::command::CommandNames::SET == commandName)
        {
            ret = createSetD2010Eprocessor(device);
        }
        else if (core::command::CommandNames::ENERGY == commandName)
        {
            ret = createEnergyD2010Eprocessor(device);
        }
        else if (core::command::CommandNames::POWER == commandName)
        {
            ret = createPowerD2010Eprocessor(device);
        }
    }

    if (nullptr == ret)
    {
        pfWarning8(s_EnoceanLogChannel) << QObject::tr("type de commande %1 non acceptée par le modèle de device %2").arg(commandName, deviceModelName);
    }

    return ret;
}

D201StatusQuery *EnoceanOperatingDeviceProcessorBuilder::createSynchronizeD20112processor(const infrastructure::QspDevice& device)
{
    return new D201StatusQuery{device};
}

D201SetOutput *EnoceanOperatingDeviceProcessorBuilder::createSetD20112processor(const infrastructure::QspDevice& device)
{
    return new D201SetOutput{device};
}

D201PilotWireModeQuery *EnoceanOperatingDeviceProcessorBuilder::createSynchronizeD2010Cprocessor(const infrastructure::QspDevice &device)
{
    return new D201PilotWireModeQuery{device};
}

D201SetPilotWireMode *EnoceanOperatingDeviceProcessorBuilder::createSetD2010Cprocessor(const infrastructure::QspDevice &device)
{
    return new D201SetPilotWireMode{device};
}

D201MeasurementEnergyQuery *EnoceanOperatingDeviceProcessorBuilder::createEnergyD2010Cprocessor(const infrastructure::QspDevice &device)
{
    return new D201MeasurementEnergyQuery{device};
}

D201MeasurementPowerQuery *EnoceanOperatingDeviceProcessorBuilder::createPowerD2010Cprocessor(const infrastructure::QspDevice &device)
{
    return new D201MeasurementPowerQuery{device};
}

D201StatusQuery *EnoceanOperatingDeviceProcessorBuilder::createSynchronizeD2010Eprocessor(const infrastructure::QspDevice &device)
{
    return new D201StatusQuery{device};
}

D201SetOutput *EnoceanOperatingDeviceProcessorBuilder::createSetD2010Eprocessor(const infrastructure::QspDevice &device)
{
    return new D201SetOutput{device};
}

D201MeasurementEnergyQuery *EnoceanOperatingDeviceProcessorBuilder::createEnergyD2010Eprocessor(const infrastructure::QspDevice &device)
{
    return new D201MeasurementEnergyQuery{device};
}

D201MeasurementPowerQuery *EnoceanOperatingDeviceProcessorBuilder::createPowerD2010Eprocessor(const infrastructure::QspDevice &device)
{
    return new D201MeasurementPowerQuery{device};
}
