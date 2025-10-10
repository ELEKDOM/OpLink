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


#ifndef ENOCEANOPERATINGDEVICEPROCESSORBUILDER_H
#define ENOCEANOPERATINGDEVICEPROCESSORBUILDER_H

#include "enoceandeviceprocessorbuilder.h"
#include "enoceaninfrastructure_forward.h"
#include "command/command-names.h"
#include "abstract_infrastructure/infrastructure-names.h"

using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class EnoceanOperatingDeviceProcessorBuilder : public EnoceanDeviceProcessorBuilder
{
public:
    EnoceanOperatingDeviceProcessorBuilder();
    ~EnoceanOperatingDeviceProcessorBuilder() override;

protected:
    infrastructure::DeviceCommandProcessor *createDeviceProcessor(const command::CommandName& commandName,
                                                                     const infrastructure::DeviceModelName& deviceModelName,
                                                                     const infrastructure::QspDevice& device) override;
    virtual D201StatusQuery *createSynchronizeD20112processor(const infrastructure::QspDevice& device);
    virtual D201SetOutput *createSetD20112processor(const infrastructure::QspDevice& device);
    virtual D201PilotWireModeQuery *createSynchronizeD2010Cprocessor(const infrastructure::QspDevice& device);
    virtual D201SetPilotWireMode *createSetD2010Cprocessor(const infrastructure::QspDevice& device);
    virtual D201MeasurementEnergyQuery *createEnergyD2010Cprocessor(const infrastructure::QspDevice& device);
    virtual D201MeasurementPowerQuery *createPowerD2010Cprocessor(const infrastructure::QspDevice& device);
    virtual D201StatusQuery *createSynchronizeD2010Eprocessor(const infrastructure::QspDevice& device);
    virtual D201SetOutput *createSetD2010Eprocessor(const infrastructure::QspDevice& device);
    virtual D201MeasurementEnergyQuery *createEnergyD2010Eprocessor(const infrastructure::QspDevice& device);
    virtual D201MeasurementPowerQuery *createPowerD2010Eprocessor(const infrastructure::QspDevice& device);
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ENOCEANOPERATINGDEVICEPROCESSORBUILDER_H
