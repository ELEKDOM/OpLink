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

#ifndef HEATINGMANAGERWIDGETBUILDER_H
#define HEATINGMANAGERWIDGETBUILDER_H

#include "ui/monitoredobservables/widget/monitoredobservablewidgetbuilder.h"

class HeatingManagerWidgetBuilder : public MonitoredObservableWidgetBuilder
{
private:
private:
    static QString hm_pw() {return QStringLiteral("heating_manager_pilotwire");}
    static QString hm_pw_thermostat() {return QStringLiteral("heating_manager_pilotwire_thermostat");}

public:
    HeatingManagerWidgetBuilder();
    ~HeatingManagerWidgetBuilder() override;

protected:
    MonitoredObservableWidgetCtrl *createWidget(QString observableName,
                                                QString observableTitle,
                                                QString observableType,
                                                QString observableLocalisation) override;
    virtual     MonitoredObservableWidgetCtrl *createHeatingManagerPwWidget(QString observableName,
                                                                            QString observableTitle,
                                                                            QString observableType,
                                                                            QString observableLocalisation);
    virtual     MonitoredObservableWidgetCtrl *createHeatingManagerPwThermostatWidget(QString observableName,
                                                                                      QString observableTitle,
                                                                                      QString observableType,
                                                                                      QString observableLocalisation);

    QString getFamilyName(const QString& observableType) override;
};

#endif // HEATINGMANAGERWIDGETBUILDER_H
