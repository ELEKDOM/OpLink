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

#ifndef OLCORE_BACKEND_LIB_FORWARD_H
#define OLCORE_BACKEND_LIB_FORWARD_H

#include <QSharedPointer>

namespace oplink
{
    class Observable;
    class ObservableSubscriber;
    //
    class SchedulableObservable;
    //
    class SupervisorObservable;
    //
    class Property;
    //
    class CommandProcessor;
    //
    class DeviceHook;
    class DeviceChannelsBinding;
    class ActuatorOutputsBinding;
    class OperationDeviceCommandProcessor;
    //
    class SubscribeSession;
    //
    class StateToWatch;
    class GroupToWatch;
    //
    class VirtualEquipmentSetLoader;
    class VirtualEquipmentSet;
    class VirtualEquipmentSetService;
    class VirtualEquipmentLoader;
    //
    class LoadBuilderArgs;
    class ActuatorBuilderArgs;
    class SensorBuilderArgs;
    //
    class InfrastructureLoader;
    class InfrastructureLoadingOperations;
    class InfrastructureControlService;
    class InfrastructureStore;
}
#endif // OLCORE_BACKEND_LIB_FORWARD_H
