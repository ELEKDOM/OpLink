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

#ifndef HEATINGMANAGERLOADER_H
#define HEATINGMANAGERLOADER_H

#include "scheduler/schedulerbuilder.h"
#include "abstract_virtualequipementset/loading/virtualequipmentloader.h"
#include "observable/highobservable/monitor/grouptowatch.h"
#include "observable/heatingmanager/heatingmanagerloaderhook.h"
#include "heatingmanagerset_forward.h"

class HeatingManagerLoader : public oplink::VirtualEquipmentLoader,
                             public oplink::HeatingManagerLoaderHook
{

public:
    HeatingManagerLoader(oplink::VirtualEquipmentSet *veSet);
    ~HeatingManagerLoader() override;

protected:// Hook
    void browseBegin() override;
    void browseEnd() override;
    bool heatingManagerDeclarationBegin(const QString& observableName,
                                        const QString& modelName,
                                        const QString& title,
                                        const QString& localisation,
                                        HeatingManagerLoaderHook::ControlType controlType,
                                        int confId) override;
    bool heatingManagerDeclarationEnd() override;
    bool controlDeclarationBegin(const QString& mode,
                                 bool windowOpeningDetection,
                                 bool presenceDetection,
                                 double threshold,
                                 double maxTemp) override;
    bool controlDeclarationEnd() override;
    plugframe::SchedulerElementHook& schedulerDeclarationBegin() override;
    bool schedulerDeclarationEnd() override;
    bool roomsDeclarationBegin() override;
    bool roomsDeclarationEnd() override;
    bool roomDeclarationBegin(const QString& roomName) override;
    bool roomDeclarationEnd() override;
    bool heatersDeclarationBegin() override;
    bool heatersDeclarationEnd() override;
    bool heaterRefDeclaration(const QString& heaterName,const QString& heaterPropertyName) override;
    bool windowSensorsDeclarationBegin() override;
    bool windowSensorsDeclarationEnd() override;
    bool windowSensorRefDeclaration(const QString& windowSensorName,const QString& windowSensorPropertyName) override;
    bool temperatureSensorsDeclarationBegin() override;
    bool temperatureSensorsDeclarationEnd() override;
    bool temperatureSensorRefDeclaration(const QString& temperatureSensorName,
                                         const QString& temperatureSensorPropertyName) override;

protected: // Loader
    oplink::VirtualEquipmentLoaderHook& loaderHook() override;

protected:
    virtual HeatingManager *createHeatingManager();
    virtual PilotWireControlRoom *createControlRoom();

private:
    void buildRoomProperties(const QString& roomName,
                             oplink::QspMonitoredObservableGroup roomGroup);
private:
    HeatingManager                     *m_newHeatingManager;
    plugframe::QspSchedulerBuilder      m_schedulerBuilder;
    oplink::QspMonitoredObservableGroup m_monitoredRoom;
    ControlType                         m_ctrT;
    bool                                m_wo_detection ,m_p_detection;
    double                              m_max_temp, m_threshold;
};

#endif // HEATINGMANAGERLOADER_H
