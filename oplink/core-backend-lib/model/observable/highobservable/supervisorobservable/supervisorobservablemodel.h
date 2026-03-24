#ifndef SUPERVISOROBSERVABLEMODEL_H
#define SUPERVISOROBSERVABLEMODEL_H

#include "model/observable/highobservable/highobservablemodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT SupervisorObservableModel : public HighObservableModel
{
public:
    SupervisorObservableModel(const ObservableModelName& name);
    ~SupervisorObservableModel() override;

protected:
    StateToWatch *createStateToWatch(const ObservableName& observableName,
                                     const PropertyName& propertyName,
                                     const QspObservableBuilderArgs& builderArgs);
};
}//namespace oplink
#endif // SUPERVISOROBSERVABLEMODEL_H
