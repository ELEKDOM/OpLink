#include "supervisorobservablebuilderargs.h"

oplink::SupervisorObservableBuilderArgs::SupervisorObservableBuilderArgs(const ObservableName &observableName,
                                                                         const ObservableModelName &observableModelName,
                                                                         const LocalisationName &observableLocalisation,
                                                                         bool activated):
    HighObservableBuilderArgs{observableName,
                              observableModelName,
                              observableLocalisation,
                              activated}
{

}

oplink::SupervisorObservableBuilderArgs::~SupervisorObservableBuilderArgs()
{

}
