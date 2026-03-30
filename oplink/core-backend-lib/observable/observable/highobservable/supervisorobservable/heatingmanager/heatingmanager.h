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

#ifndef HEATINGMANAGER_H
#define HEATINGMANAGER_H

#include <QStringLiteral>
#include "observable/observable/highobservable/supervisorobservable/supervisorobservable.h"

namespace oplink
{
///
/// \brief The HeatingManager class
/// The heating manager is a virtual device whose role is to control a set of radiators (radiator management zone).
/// The controlled radiators are assigned to specific rooms. Multiple radiators can be assigned to a single room.
/// One heating manager can control multiple rooms. The radiators are controlled via pilot wire.
///
/// The controller transmits the pilot wire command to the radiators according to a setpoint.
/// There are two types of controllers:
///     1. Pilot wire control unit.
///         In this case, the setpoint is directly the pilot wire mode to be applied.
///     2. Thermostat.
///         In this case, the setpoint is a temperature to be regulated.
///         The controller operates the radiators with only two pilot wire commands (comfort and off).
///         The temperature sensors to be taken into account for each room should be declared.
///
/// Furthermore, the setpoint to be followed can be provided to the controller in two ways:
///     1. By the user (on-demand mode).
///     2. By a scheduler, depending on its configuration (planned mode).
///         The planned mode is optional. It requires the declaration of a scheduler.
///
/// The algorithm has an option to turn off the radiators when a window is opened.
/// In this case, you must declare all the detectors to be monitored.
///
/// A heating manager also has an on/off mode.
///
/// A heating manager is created from an XML file that provides its configuration.
///
/// The setpoint managed by the heating manager applies to all rooms.
/// However, the heating manager accepts a set command allowing to assign a setpoint to a single room only.
///
/// When a radiator is controlled by a heating manager,
/// the manager overrides any pilot wire commands sent directly to the radiator.
/// The heating manager must be switched off before you can directly control one of the radiators it manages!
///
/// When a heating manager is in planned mode and receives a command to modify the general setpoint (or setpoint of a room),
/// the setpoint is applied and the heating manager switches to derogated mode until the next setpoint is transmitted by the scheduler.
///
/// The heating managers are built from two models created and then loaded at the beginning of the startup phase of loading the XML description files.
///
/// A heating manager is an observable. Its specific properties are:
///
/// 	[running] boolean true (on) false (off)
/// 	[trigger_mode] string (ondemand or planned), only for manager with scheduler
/// 	[schedulerxmldef] string (scheduler definition in xml, useful for frontend)
/// 	[setpoint] string (pw order or temp value)
/// 	[derogated] boolean (only for trigger_mode planned)
///
/// 	Set of "Properties" per room (each property are prefixed by the room name):
/// 	[setpoint] string specific room setpoint
/// 	[wclosed] boolean true (all windows are closed) false (at least one window is open)
/// 	[temperature] float (last temperature sent by one of the room's sensors)
///
/// The manager accepts the "set" command that allow, at runtime, the modification of some of its properties.
///
class OLCORE_BACKEND_LIB_EXPORT HeatingManager : public oplink::SupervisorObservable
{
public:
    static QString heaterCategory() {return QStringLiteral("heater");}
    static QString windowSensorCategory() {return QStringLiteral("windowsensor");}
    static QString temperatureSensorCategory() {return QStringLiteral("temperaturesensor");}

public:
    HeatingManager(QString defaultSetpoint,const plugframe::QspScheduler& scheduler);
    ~HeatingManager() override;

public: // for algorithm
    bool windowSensorState(const QString& roomName, bool allClosed);

public: // for processor
    bool isActivated();
    void setOn();
    void setOff();
    void setSetpoint(const QString& setpoint);
    void setRoomSetpoint(const QString& roomName, const QString& setpoint);
    void setOnDemand();
    void setPlanned();
    void setSchedulerXmlDef(const QString& xmlDef);

protected:
    void init() override;
    void onSchedulerEvt(QString evt) override;
    void onDailySequencerIndex(int idx) override;
    void onWeeklySequencer(QString name) override;
    void onDailySequencer(QString name) override;

private:
    void startPlanning();
    void startRoomsMonitor();
    void stopRoomsMonitor();
    const QString setpointProperty();
    void setpointProperty(const QString& setpoint);
    const bool derogatedProperty();
    void derogatedProperty(bool derog);
    const QString roomSetpointProperty(const QString& roomName);
    void roomSetpointProperty(const QString& roomName,const QString& order);
    void processScheduledSetpoint(const QString& setpoint);
    void setpointForRoom(const QString& setpoint,const QString& roomName);
    void setpointForRooms(const QString& setpoint);
    void checkForDerogatedState();

private:
    QString m_defaultSetpoint;

};
}//namespace oplink
#endif // HEATINGMANAGER_H
