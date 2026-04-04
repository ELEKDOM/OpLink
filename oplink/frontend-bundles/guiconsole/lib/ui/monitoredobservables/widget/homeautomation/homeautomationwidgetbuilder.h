// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#ifndef HOMEAUTOMATIONWIDGETBUILDER_H
#define HOMEAUTOMATIONWIDGETBUILDER_H

#include "ui/monitoredobservables/widget/monitoredobservablewidgetbuilder.h"

class HomeAutomationWidgetBuilder : public MonitoredObservableWidgetBuilder
{
private:
    static QString onOffLighting() {return QStringLiteral("onoff_lighting");}
    static QString heatingPw() {return QStringLiteral("pw_electric_heating");}
    static QString heatingPwMeasurement() {return QStringLiteral("pw_electric_heating_measurement");}
    static QString onOffPlug() {return QStringLiteral("onoff_smart_plug");}
    static QString onOffPlugMeasurement() {return QStringLiteral("onoff_smart_plug_measurement");}
    static QString temperatureHumidity() {return QStringLiteral("temperature_humidity_sensor");}
    static QString windowSensor() {return QStringLiteral("window_sensor");}

public:
    HomeAutomationWidgetBuilder();
    ~HomeAutomationWidgetBuilder() override;

protected:
    MonitoredObservableWidgetCtrl *createWidget(QString observableName,
                                                QString observableTitle,
                                                QString observableType,
                                                QString observableLocalisation) override;

    virtual MonitoredObservableWidgetCtrl *createLightingWidget(QString observableName,
                                                                QString observableTitle,
                                                                QString observableType,
                                                                QString observableLocalisation);

    virtual MonitoredObservableWidgetCtrl *createHeating6mWidget(QString observableName,
                                                                 QString observableTitle,
                                                                 QString observableType,
                                                                 QString observableLocalisation);

    virtual MonitoredObservableWidgetCtrl *createSmartPlugWidget(QString observableName,
                                                                 QString observableTitle,
                                                                 QString observableType,
                                                                 QString observableLocalisation);

    virtual MonitoredObservableWidgetCtrl *createTemperatureHumidityWidget(QString observableName,
                                                                           QString observableTitle,
                                                                           QString observableType,
                                                                           QString observableLocalisation);

    virtual MonitoredObservableWidgetCtrl *createWindowSensorWidget(QString observableName,
                                                                    QString observableTitle,
                                                                    QString observableType,
                                                                    QString observableLocalisation);

    QString getFamilyName(const QString& observableType) override;
};

#endif // HOMEAUTOMATIONWIDGETBUILDER_H
