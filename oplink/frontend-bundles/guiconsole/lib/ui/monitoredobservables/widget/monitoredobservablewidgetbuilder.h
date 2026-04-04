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

#ifndef MONITOREDOBSERVABLEWIDGETBUILDER_H
#define MONITOREDOBSERVABLEWIDGETBUILDER_H

#include <QString>
#include <QSharedPointer>
#include "olfconsole_forward.h"

class MonitoredObservableWidgetBuilder
{
public:
    MonitoredObservableWidgetBuilder();
    virtual ~MonitoredObservableWidgetBuilder();

public:
    virtual MonitoredObservableWidgetCtrl *buildWidget(QString observableName,
                                                       QString observableTitle,
                                                       QString observableType,
                                                       QString observableLocalisation);
    virtual QString getFamilyName(const QString& observableType) = 0;

protected:
    virtual MonitoredObservableWidgetCtrl *createWidget(QString observableName,
                                                        QString observableTitle,
                                                        QString observableType,
                                                        QString observableLocalisation) = 0;
};
using QspMonitoredObservableWidgetBuilder = QSharedPointer<MonitoredObservableWidgetBuilder>;
#endif // MONITOREDOBSERVABLEWIDGETBUILDER_H
