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


#ifndef OPERATIONDEVICE_H
#define OPERATIONDEVICE_H

#include <QVector>
#include <QHash>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "observable/lowobservable/lowobservable.h"
#include "abstract_infrastructure/device/devicehook.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{

///
/// \brief The OperationDevice class.
///        Base class of an object associated with an architecture (sensor, actuator, etc).
class OLCORE_BACKEND_LIB_EXPORT OperationDevice : public LowObservable, public infrastructure::DeviceHook
{
public:
    OperationDevice();
    ~OperationDevice() override;

protected:
    void setDevice(infrastructure::QspDevice device) override;
    infrastructure::QspDevice device() override;
    void bindChannels(const infrastructure::DeviceChannelsBinding& deviceChannelsBinding) override;
    void setChannelValue(int idx, QVariant value) override;
    bool getChannelIdx(const PropertyName& propertyName, int& idx) override;
    bool hasChannel(int idx) override;

private:
    void bindChannel(int index, const PropertyName& pname);

private:
    infrastructure::QspDevice           m_device;
    QVector<QspOperationDeviceProperty> m_channels;
    QHash<PropertyName, int>            m_reverseChannels;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OPERATIONDEVICE_H
