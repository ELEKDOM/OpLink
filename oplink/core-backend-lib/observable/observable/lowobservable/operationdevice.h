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
#include "observable/observable/lowobservable/lowobservable.h"
#include "observable/property/operationdeviceproperty.h"
#include "abstract_infrastructure/device/devicehook.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
///
/// \brief The OperationDevice class.
///        Base class of an object associated with an architecture (sensor, actuator, etc).
class OLCORE_BACKEND_LIB_EXPORT OperationDevice : public LowObservable, public DeviceHook
{
public:
    OperationDevice();
    ~OperationDevice() override;

protected:
    void setDevice(QspDevice device) override;
    QspDevice device() override;
    void bindChannels(const DeviceChannelsBinding& deviceChannelsBinding) override;
    void setChannelValue(int idx, QVariant value) override;
    bool getChannelIdx(const PropertyName& propertyName, int& idx) override;
    bool hasChannel(int idx) override;

private:
    void bindChannel(int index, const PropertyName& pname);

private:
    QspDevice                           m_device;
    QVector<QspOperationDeviceProperty> m_channels;
    QHash<PropertyName, int>            m_reverseChannels;
};
}//namespace oplink
#endif // OPERATIONDEVICE_H
