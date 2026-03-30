#include "highcommandprocessor.h"

oplink::HighCommandProcessor::HighCommandProcessor(Observable &observable,
                                                   const CommandName &cmdName):
    CommandProcessor{observable, cmdName}
{

}

oplink::HighCommandProcessor::~HighCommandProcessor()
{

}
