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


//class InfrastructureLoader;
//class Area;
//class DeviceBuilder;
//
//
//class AreaGateway;
//class Device;
//
//class DeviceProcessorBuilder;
//class DeviceCommandProcessor;
//class InfrastructureStore;
//class InfrastructureLoadingOperations;
//class InfrastructureLoaderArgs;
//class InfrastructureLoaderOuts;
//class InfrastructureWorkerOuts;
//

//        using QspAreaGateway = QSharedPointer<AreaGateway>;
//        using QspDevice  = QSharedPointer<Device>;
//        using QspArea = QSharedPointer<Area>;
//        using QspDeviceCommandProcessor  = QSharedPointer<DeviceCommandProcessor>;
//        using QspDeviceHook  = QSharedPointer<DeviceHook>;
//        using QspActuatorOutputsBinding = QSharedPointer<ActuatorOutputsBinding>;
//        using QspDeviceProcessorBuilder  = QSharedPointer<DeviceProcessorBuilder>;
//        using QspDeviceBuilder  = QSharedPointer<DeviceBuilder>;
//        using QspInfrastructureLoader = QSharedPointer<InfrastructureLoader>;
//        using QspDeviceInfrastructureLoaderArgs = QSharedPointer<InfrastructureLoaderArgs>;
//        using QspInfrastructureLoaderOuts = QSharedPointer<InfrastructureLoaderOuts>;
//        using QspInfrastructureWorkerOuts = QSharedPointer<InfrastructureWorkerOuts>;

//class InfrastructureControlService;
//

//            using QspInfrastructureControlService = QSharedPointer<InfrastructureControlService>;
//
//class Infrastructure;
//
//class LoadBuilderArgs;
//class ActuatorBuilderArgs;
//class SensorBuilderArgs;
//class OperationDeviceBuilderArgs;
//class ObservablePropertyModel;
//class CommandProcessorModel;
//class ObservableModel;
//class ObservableBuilderArgs;
//
//        using QspActuatorBuilderArgs = QSharedPointer<ActuatorBuilderArgs>;
//        using QspObservableBuilderArgs = QSharedPointer<ObservableBuilderArgs>;//
//        using QspLoadBuilderArgs = QSharedPointer<LoadBuilderArgs>;
//        using QspOperationDeviceBuilderArgs = QSharedPointer<OperationDeviceBuilderArgs>;
//        using QspSensorBuilderArgs = QSharedPointer<SensorBuilderArgs>;
//        using QspObservablePropertyModel = QSharedPointer<ObservablePropertyModel>;
//        using QspCommandProcessorModel = QSharedPointer<CommandProcessorModel>;
//        using QspObservableModel = QSharedPointer<ObservableModel>;
//
//class ObservableBuildersContainer;
//class ObservableBuilder;
//class Observable;
//class SupervisorObservable;
//class Property;
//class CommandProcessor;
//
//class LoadProperty;
//class LowProperty;
//class OperationDeviceProperty;
//
//class ObservableNotifier;
//class SchedulableObservable;

//using QspObservableBuildersContainer = QSharedPointer<ObservableBuildersContainer>;
//using QspObservableBuilder = QSharedPointer<ObservableBuilder>;
//using QspObservable = QSharedPointer<Observable>;
//using QspProperty  = QSharedPointer<Property>;
//using QspOperationDeviceProperty  = QSharedPointer<OperationDeviceProperty>;
//using QspLowProperty = QSharedPointer<LowProperty>;
//using QspLoadProperty = QSharedPointer<LoadProperty>;
//using QspCommandProcessor  = QSharedPointer<CommandProcessor>;
//using QspObservableNotifier = QSharedPointer<ObservableNotifier>;
//using QspVirtualEquipment = QSharedPointer<SchedulableObservable>;
//
//class StateToWatchList;
//class StateToWatch;
//class GroupToWatch;
//class GroupToWatchAlgorithm;

//using QspMonitoredStateList = QSharedPointer<StateToWatchList>;
//using QspMonitoredState = QSharedPointer<StateToWatch>;
//using QspMonitoredObservableGroup = QSharedPointer<GroupToWatch>;
//using QspMonitoredGroupAlgorithm = QSharedPointer<GroupToWatchAlgorithm>;
//
//class ObservableStates;
//
//class SessionConfLoader;

//using QspObservableStates = QSharedPointer<ObservableStates>;
//using QspSubscribeSession = QSharedPointer<SubscribeSession>;
//
//class Command;

//        using QspCommand  = QSharedPointer<Command>;

//class VirtualEquipmentLoader;

//using QspVirtualEquipmentLoader = QSharedPointer<VirtualEquipmentLoader>;

//class VirtualEquipmentSetLoader;
//class VirtualEquipmentSetLoaderOuts;
//class VirtualEquipmentSetLoaderArgs;

//using QspVirtualEquipmentSetLoader = QSharedPointer<VirtualEquipmentSetLoader>;
//using QspVirtualEquipmentSetLoaderOuts = QSharedPointer<VirtualEquipmentSetLoaderOuts>;
//using QSpVirtualEquipmentSetLoaderArgs = QSharedPointer<VirtualEquipmentSetLoaderArgs>;


//class VirtualEquipmentSetService;

//using QspVirtualEquipmentSetService = QSharedPointer<VirtualEquipmentSetService>;

//class VirtualEquipmentSet;
}
#endif // OLCORE_BACKEND_LIB_FORWARD_H
