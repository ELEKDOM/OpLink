#include "monitoredobservablewidgetbuilder.h"
#include "monitoredobservablewidgetctrl.h"

MonitoredObservableWidgetBuilder::MonitoredObservableWidgetBuilder() {}

MonitoredObservableWidgetBuilder::~MonitoredObservableWidgetBuilder()
{

}

MonitoredObservableWidgetCtrl *MonitoredObservableWidgetBuilder::buildWidget(QString observableName,
                                                                             QString observableTitle,
                                                                             QString observableType,
                                                                             QString observableLocalisation)
{
    MonitoredObservableWidgetCtrl *ret;

    ret = createWidget(observableName,
                       observableTitle,
                       observableType,
                       observableLocalisation);

    if (ret)
    {
        ret->createStates();
    }

    return ret;
}
