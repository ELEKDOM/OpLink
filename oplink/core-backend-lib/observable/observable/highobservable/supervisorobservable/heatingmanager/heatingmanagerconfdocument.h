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

#ifndef HEATINGMANAGERCONFDOCUMENT_H
#define HEATINGMANAGERCONFDOCUMENT_H

#include "observable/observable/highobservable/highobservableconfdocument.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanagerloaderhook.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatingManagerConfDocument : public oplink::HighObservableConfDocument
{
private:
    static QString heatingManagerTag() {return QStringLiteral("heating-manager");}
    static QString pwControlTag() {return QStringLiteral("pw-control");}
    static QString pwtControlTag() {return QStringLiteral("pwt-control");}
    static QString roomsTag() {return QStringLiteral("rooms");}
    static QString roomTag() {return QStringLiteral("room");}
    static QString heatersTag() {return QStringLiteral("heaters");}
    static QString heaterRefTag() {return QStringLiteral("heater-ref");}
    static QString windowSensorsTag() {return QStringLiteral("window-sensors");}
    static QString windowSensorRefTag() {return QStringLiteral("window-sensor-ref");}
    static QString temperatureSensorsTag() {return QStringLiteral("temp-sensors");}
    static QString temperatureSensorRefTag() {return QStringLiteral("temp-sensor-ref");}

    static QString controlAttr() {return QStringLiteral("control");}
    static QString windowOpeningDetectionAttr() {return QStringLiteral("window-opening-detection");}
    static QString presenceDetectionAttr() {return QStringLiteral("presence-detection");}
    static QString setPointAttr() {return QStringLiteral("setpoint");}
    static QString thresholdAttr() {return QStringLiteral("threshold");}
    static QString maxTempdAttr() {return QStringLiteral("max-temp");}

    static QString controlType_pw() {return QStringLiteral("pw");}
    static QString controlType_pwt() {return QStringLiteral("pwt");}
    static QString val_yes() {return QStringLiteral("yes");}
    static QString val_on() {return QStringLiteral("on");}

public:
    HeatingManagerConfDocument(HeatingManagerLoaderHook& browserHook);
    ~HeatingManagerConfDocument() override;

protected:
    QString rootNodeName() override;
    HeatingManagerLoaderHook& hook();
    bool _browse() override;
    virtual bool extractDataFromHeatingManagerElement(QDomElement& hmElem);
    virtual bool extractDataFromControlElement(QDomElement& hmElem,
                                               const QString& observableName,
                                               HeatingManagerLoaderHook::ControlType ctrT);
    virtual bool extractDataFromRoomsElement(QDomElement& hmElem);
    virtual bool extractDataFromRoomElement(QDomElement& roomElem);
    virtual bool extractDataFromHeatersElement(QDomElement& roomElem);
    virtual bool extractDataFromWindowSensorsElement(QDomElement& roomElem);
    virtual bool extractDataFromTemperatureSensorsElement(QDomElement& roomElem);

private:
    bool extractScheduler(QDomElement& controlElemconst,const QString& observableName);
};
}//namespace oplink
#endif // HEATINGMANAGERCONFDOCUMENT_H
