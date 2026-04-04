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

#include <QObject>
#include "homeautomationwidgetbuilder.h"
#include "ui/monitoredobservables/widget/homeautomation/controller/lightingwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/controller/heating6mwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/controller/smartplugwidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/controller/temperaturehumiditywidgetctrl.h"
#include "ui/monitoredobservables/widget/homeautomation/controller/windowsensorwidgetctrl.h"

HomeAutomationWidgetBuilder::HomeAutomationWidgetBuilder() {}

HomeAutomationWidgetBuilder::~HomeAutomationWidgetBuilder()
{

}

MonitoredObservableWidgetCtrl *HomeAutomationWidgetBuilder::createWidget(QString observableName,
                                                                         QString observableTitle,
                                                                         QString observableType,
                                                                         QString observableLocalisation)
{
    MonitoredObservableWidgetCtrl *ret{nullptr};

    if (onOffLighting() == observableType)
    {
        ret = createLightingWidget(observableName,
                                   observableTitle,
                                   observableType,
                                   observableLocalisation);
    }
    else if(heatingPwMeasurement() == observableType)
    {
        ret = createHeating6mWidget(observableName,
                                    observableTitle,
                                    observableType,
                                    observableLocalisation);
    }
    else if(onOffPlugMeasurement() == observableType)
    {
        ret = createSmartPlugWidget(observableName,
                                    observableTitle,
                                    observableType,
                                    observableLocalisation);
    }
    else if(temperatureHumidity() == observableType)
    {
        ret = createTemperatureHumidityWidget(observableName,
                                              observableTitle,
                                              observableType,
                                              observableLocalisation);
    }
    else if(windowSensor() == observableType)
    {
        ret = createWindowSensorWidget(observableName,
                                       observableTitle,
                                       observableType,
                                       observableLocalisation);
    }

    return ret;
}

MonitoredObservableWidgetCtrl *HomeAutomationWidgetBuilder::createLightingWidget(QString observableName,
                                                                                 QString observableTitle,
                                                                                 QString observableType,
                                                                                 QString observableLocalisation)
{
    return new LightingWidgetCtrl(observableName,
                                  observableTitle,
                                  observableType,
                                  observableLocalisation);
}

MonitoredObservableWidgetCtrl *HomeAutomationWidgetBuilder::createHeating6mWidget(QString observableName,
                                                                                  QString observableTitle,
                                                                                  QString observableType,
                                                                                  QString observableLocalisation)
{
    return new Heating6mWidgetCtrl(observableName,
                                   observableTitle,
                                   observableType,
                                   observableLocalisation);
}

MonitoredObservableWidgetCtrl *HomeAutomationWidgetBuilder::createSmartPlugWidget(QString observableName,
                                                                                  QString observableTitle,
                                                                                  QString observableType,
                                                                                  QString observableLocalisation)
{
    return new SmartPlugWidgetCtrl(observableName,
                                   observableTitle,
                                   observableType,
                                   observableLocalisation);
}

MonitoredObservableWidgetCtrl *HomeAutomationWidgetBuilder::createTemperatureHumidityWidget(QString observableName,
                                                                                            QString observableTitle,
                                                                                            QString observableType,
                                                                                            QString observableLocalisation)
{
    return new TemperatureHumidityWidgetCtrl(observableName,
                                             observableTitle,
                                             observableType,
                                             observableLocalisation);
}

MonitoredObservableWidgetCtrl *HomeAutomationWidgetBuilder::createWindowSensorWidget(QString observableName,
                                                                                     QString observableTitle,
                                                                                     QString observableType,
                                                                                     QString observableLocalisation)
{
    return new WindowSensorWidgetCtrl(observableName,
                                      observableTitle,
                                      observableType,
                                      observableLocalisation);
}

QString HomeAutomationWidgetBuilder::getFamilyName(const QString &observableType)
{
    QString ret;

    if (observableType == onOffLighting())
    {
        ret = QObject::tr("Éclairage");
    }
    else if (observableType == heatingPw())
    {
        ret = QObject::tr("Chauffage");
    }
    else if (observableType == heatingPwMeasurement())
    {
        ret = QObject::tr("Chauffage");
    }
    else if (observableType == onOffPlug())
    {
        ret = QObject::tr("Prises commandées");
    }
    else if (observableType == onOffPlugMeasurement())
    {
        ret = QObject::tr("Prises commandées");
    }
    else if (observableType == temperatureHumidity())
    {
        ret = QObject::tr("Capteurs");
    }
    else if (observableType == windowSensor())
    {
        ret = QObject::tr("Capteurs");
    }

    return ret;
}
