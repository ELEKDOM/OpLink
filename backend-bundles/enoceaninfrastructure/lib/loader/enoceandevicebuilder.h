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

using namespace elekdom::oplink::core;

namespace elekdom
{
namespace oplink
{
namespace enocean
{

class EnoceanDeviceBuilder : public infrastructure::DeviceBuilder
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
    EnoceanDeviceBuilder(const QSharedPointer<infrastructure::DeviceProcessorBuilder>& processorBuilder);
    ~EnoceanDeviceBuilder() override;

protected:
    QSharedPointer<infrastructure::Device> createDevice(const infrastructure::DeviceId& id,
                                                           const infrastructure::DeviceModelName& deviceModelName,
                                                           infrastructure::DeviceHook& deviceHook) override;
    virtual infrastructure::Device *createD20112(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
    virtual infrastructure::Device *createD2010C(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
    virtual infrastructure::Device *createD2010E(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
    virtual infrastructure::Device *createF60101(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
    virtual infrastructure::Device *createF60201(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
    virtual infrastructure::Device *createA50401(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
    virtual infrastructure::Device *createD50001(const infrastructure::DeviceId& id,
                                                    infrastructure::DeviceHook& deviceHook);
};

}//namespace enocean
}//namespace oplink
}//namespace elekdom

#endif // ENOCEANDEVICEBUILDER_H
