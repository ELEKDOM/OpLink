#ifndef SUPERVISOROBSERVABLEBUILDERARGS_H
#define SUPERVISOROBSERVABLEBUILDERARGS_H

#include "model/observable/highobservable/highobservablebuilderargs.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT SupervisorObservableBuilderArgs : public HighObservableBuilderArgs
{
public:
    SupervisorObservableBuilderArgs(const ObservableName& observableName,
                                    const ObservableModelName& observableModelName,
                                    const LocalisationName& observableLocalisation,
                                    bool activated);

    ~SupervisorObservableBuilderArgs()override;
};
using QspSupervisorObservableBuilderArgs = QSharedPointer<SupervisorObservableBuilderArgs>;
}//namespace oplink
#endif // SUPERVISOROBSERVABLEBUILDERARGS_H
