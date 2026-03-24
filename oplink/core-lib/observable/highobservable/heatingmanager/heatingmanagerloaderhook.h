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

#ifndef HEATINGMANAGERLOADERHOOK_H
#define HEATINGMANAGERLOADERHOOK_H

#include "observable/highobservable/highobservableloaderhook.h"
#include "scheduler/schedulerelementhook.h"

namespace oplink
{
class OLCORE_LIB_EXPORT HeatingManagerLoaderHook : public HighObservableLoaderHook
{
public:
    enum class ControlType {PW,PWT,Unknow};

public:
    static QString scheduledSetPoint() {return QStringLiteral("scheduled");}

public:
    ~HeatingManagerLoaderHook() override {}

public:
    virtual bool heatingManagerDeclarationBegin(const QString& observableName,
                                                const QString& title,
                                                const QString& localisation,
                                                HeatingManagerLoaderHook::ControlType controlType,
                                                bool activated) = 0;
    virtual bool heatingManagerDeclarationEnd() = 0;
    virtual bool controlDeclarationBegin(const QString& setPointValue,
                                         double threshold,
                                         double maxTemp) = 0;
    virtual bool controlDeclarationEnd() = 0;
    virtual plugframe::SchedulerElementHook& schedulerDeclarationBegin(const QString& xmlText) = 0;
    virtual bool schedulerDeclarationEnd() = 0;
    virtual bool roomsDeclarationBegin() = 0;
    virtual bool roomsDeclarationEnd() = 0;
    virtual bool roomDeclarationBegin(const QString& roomName,
                                      bool windowOpeningDetection) = 0;
    virtual bool roomDeclarationEnd() = 0;
    virtual bool heatersDeclarationBegin() = 0;
    virtual bool heatersDeclarationEnd() = 0;
    virtual bool heaterRefDeclaration(const QString& heaterName,const QString& heaterPropertyName) = 0;
    virtual bool windowSensorsDeclarationBegin() = 0;
    virtual bool windowSensorsDeclarationEnd() = 0;
    virtual bool windowSensorRefDeclaration(const QString& windowSensorName,const QString& windowSensorPropertyName) = 0;
    virtual bool temperatureSensorsDeclarationBegin() = 0;
    virtual bool temperatureSensorsDeclarationEnd() = 0;
    virtual bool temperatureSensorRefDeclaration(const QString& temperatureSensorName,const QString& temperatureSensorPropertyName) = 0;
};
}//namespace oplink
#endif // HEATINGMANAGERLOADERHOOK_H
