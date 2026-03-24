#include "supervisorobservablemodel.h"
#include "observable/observable/highobservable/supervisorobservable/monitor/statetowatch.h"
#include "model/observable/highobservable/supervisorobservable/supervisorobservablebuilderargs.h"

oplink::SupervisorObservableModel::SupervisorObservableModel(const ObservableModelName &name):
    HighObservableModel{name}
{

}

oplink::SupervisorObservableModel::~SupervisorObservableModel()
{

}

oplink::StateToWatch *oplink::SupervisorObservableModel::createStateToWatch(const ObservableName &observableName,
                                                                            const PropertyName &propertyName,
                                                                            const QspObservableBuilderArgs& builderArgs)
{
    StateToWatch *ret{nullptr};
    const QspSupervisorObservableBuilderArgs& supBuilderArgs{builderArgs.dynamicCast<SupervisorObservableBuilderArgs>()};
    oplink::QspProperty property;

    property = (supBuilderArgs->m_observableService)->property(observableName,propertyName);
    if (!property.isNull())
    {
        ret = new oplink::StateToWatch(property);
    }

    return ret;
}
