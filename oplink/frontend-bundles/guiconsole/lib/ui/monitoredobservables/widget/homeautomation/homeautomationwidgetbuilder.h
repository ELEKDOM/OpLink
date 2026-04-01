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
