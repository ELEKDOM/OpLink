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
