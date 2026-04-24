#include "heatingmanagercmdprocessor.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanager.h"

oplink::HeatingManagerCmdProcessor::HeatingManagerCmdProcessor(Observable &observable,
                                                               const CommandName &cmdName):
    HighCommandProcessor{observable,cmdName}
{

}

oplink::HeatingManagerCmdProcessor::~HeatingManagerCmdProcessor()
{

}

oplink::HeatingManager &oplink::HeatingManagerCmdProcessor::manager()
{
    return dynamic_cast<oplink::HeatingManager&>(observable());
}
