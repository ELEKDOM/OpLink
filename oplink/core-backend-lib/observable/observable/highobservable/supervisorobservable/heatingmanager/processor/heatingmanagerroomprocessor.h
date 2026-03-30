#ifndef HEATINGMANAGERROOMPROCESSOR_H
#define HEATINGMANAGERROOMPROCESSOR_H

#include "observable/observable/highobservable/supervisorobservable/heatingmanager/processor/heatingmanagercmdprocessor.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT  HeatingManagerRoomProcessor : public HeatingManagerCmdProcessor
{
public:
    HeatingManagerRoomProcessor(Observable& observable);
    ~HeatingManagerRoomProcessor() override;

protected:
    void process(QspCommand order) override;
};
}//namespace oplink
#endif // HEATINGMANAGERROOMPROCESSOR_H
