#ifndef LOWOBSERVABLEMODEL_H
#define LOWOBSERVABLEMODEL_H

#include "model/observable/observablemodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT LowObservableModel : public ObservableModel
{
public:
    LowObservableModel(const ObservableModelName& name);
    ~LowObservableModel() override;
};
}//namespace oplink
#endif // LOWOBSERVABLEMODEL_H
