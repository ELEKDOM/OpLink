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


#include "monitoredobservablebuilder.h"
#include "pageviewlayoutbuilder.h"
#include "ui/olfmonitoredobservablescontroller.h"
#include "ui/monitoredobservables/widget/lightingwidgetctrl.h"
#include "ui/monitoredobservables/widget/heating6mwidgetctrl.h"
#include "ui/monitoredobservables/widget/smartplugwidgetctrl.h"
#include "ui/monitoredobservables/widget/temperaturehumiditywidgetctrl.h"
#include "ui/monitoredobservables/widget/windowsensorwidgetctrl.h"

using namespace elekdom::oplink::frontend::guiconsole::monitoredobservable;

MonitoredObservableBuilder::MonitoredObservableBuilder(OlfMonitoredObservablesController& controller,
                                                       PageViewLayoutBuilder *viewsBuilder):
    m_controller{controller}
{
    m_viewsBuilder.reset(viewsBuilder);
    m_viewsBuilder->setBuilder(this);
}

MonitoredObservableBuilder::~MonitoredObservableBuilder()
{

}

QString MonitoredObservableBuilder::getFamilyName(const QString &observableType)
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

void MonitoredObservableBuilder::browseBegin()
{

}

void MonitoredObservableBuilder::browseEnd()
{
    m_controller.endOfLoadingViews();
}

void MonitoredObservableBuilder::beginObservableDeclaration(QString observableName,
                                                            QString observableTitle,
                                                            QString observableType,
                                                            QString observableLocalisation)
{
    m_creatingWidget.reset(createWidget(observableName,
                                        observableTitle,
                                        observableType,
                                        observableLocalisation));
}

void MonitoredObservableBuilder::endObservableDeclaration()
{
    if(!m_creatingWidget.isNull())
    {
        m_viewsBuilder->assignWidgetView(m_controller,m_creatingWidget);
        m_controller.addMonitoredObservable(m_creatingWidget);
    }
}

void MonitoredObservableBuilder::propertyDeclaration(QString propertyName)
{
    if(!m_creatingWidget.isNull())
    {
        m_creatingWidget->addState(propertyName);
    }
}

widget::MonitoredObservableWidgetCtrl *MonitoredObservableBuilder::createWidget(QString observableName,
                                                                                QString observableTitle,
                                                                                QString observableType,
                                                                                QString observableLocalisation)
{
    widget::MonitoredObservableWidgetCtrl *ret{nullptr};

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

widget::MonitoredObservableWidgetCtrl *MonitoredObservableBuilder::createLightingWidget(QString observableName,
                                                                                        QString observableTitle,
                                                                                        QString observableType,
                                                                                        QString observableLocalisation)
{
    return new widget::LightingWidgetCtrl(observableName,
                                          observableTitle,
                                          observableType,
                                          observableLocalisation);
}

widget::MonitoredObservableWidgetCtrl *MonitoredObservableBuilder::createHeating6mWidget(QString observableName,
                                                                                         QString observableTitle,
                                                                                         QString observableType,
                                                                                         QString observableLocalisation)
{
    return new widget::Heating6mWidgetCtrl(observableName,
                                           observableTitle,
                                           observableType,
                                           observableLocalisation);
}

widget::MonitoredObservableWidgetCtrl *MonitoredObservableBuilder::createSmartPlugWidget(QString observableName,
                                                                                         QString observableTitle,
                                                                                         QString observableType,
                                                                                         QString observableLocalisation)
{
    return new widget::SmartPlugWidgetCtrl(observableName,
                                           observableTitle,
                                           observableType,
                                           observableLocalisation);
}

widget::MonitoredObservableWidgetCtrl *MonitoredObservableBuilder::createTemperatureHumidityWidget(QString observableName,
                                                                                                   QString observableTitle,
                                                                                                   QString observableType,
                                                                                                   QString observableLocalisation)
{
    return new widget::TemperatureHumidityWidgetCtrl(observableName,
                                                     observableTitle,
                                                     observableType,
                                                     observableLocalisation);
}

widget::MonitoredObservableWidgetCtrl *MonitoredObservableBuilder::createWindowSensorWidget(QString observableName,
                                                                                            QString observableTitle,
                                                                                            QString observableType,
                                                                                            QString observableLocalisation)
{
    return new widget::WindowSensorWidgetCtrl(observableName,
                                              observableTitle,
                                              observableType,
                                              observableLocalisation);
}
