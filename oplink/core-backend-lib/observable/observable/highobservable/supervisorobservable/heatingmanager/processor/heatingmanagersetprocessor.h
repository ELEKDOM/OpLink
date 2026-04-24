#ifndef HEATINGMANAGERSETPROCESSOR_H
#define HEATINGMANAGERSETPROCESSOR_H

#include "observable/observable/highobservable/supervisorobservable/heatingmanager/processor/heatingmanagercmdprocessor.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatingManagerSetProcessor : public HeatingManagerCmdProcessor
{
public:
    HeatingManagerSetProcessor(Observable& observable);
    ~HeatingManagerSetProcessor();

protected:
    void process(QspCommand order) override;
};
}//namespace oplink
#endif // HEATINGMANAGERSETPROCESSOR_H
