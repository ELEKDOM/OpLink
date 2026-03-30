#ifndef HIGHCOMMANDPROCESSOR_H
#define HIGHCOMMANDPROCESSOR_H

#include "observable/processor/commandprocessor.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HighCommandProcessor : public CommandProcessor
{
public:
    HighCommandProcessor(Observable& observable,
                         const CommandName& cmdName);
    ~HighCommandProcessor() override;
};
}//namespace oplink
#endif // HIGHCOMMANDPROCESSOR_H
