#ifndef HEATINGMANAGERCMDPROCESSOR_H
#define HEATINGMANAGERCMDPROCESSOR_H

#include "observable/processor/highprocessor/highcommandprocessor.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatingManagerCmdProcessor : public HighCommandProcessor
{
public:
    HeatingManagerCmdProcessor(Observable& observable,
                               const CommandName& cmdName);
    ~HeatingManagerCmdProcessor() override;

protected:
    HeatingManager& manager();
};
}//namespace oplink
#endif // HEATINGMANAGERCMDPROCESSOR_H
