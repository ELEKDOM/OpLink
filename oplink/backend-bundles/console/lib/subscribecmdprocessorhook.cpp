#include "subscribecmdprocessorhook.h"
#include "subscribecmdprocessor.h"

SubscribeCmdProcessorHook::SubscribeCmdProcessorHook(SubscribeCmdProcessor &processor):
    m_processor{processor}
{

}

SubscribeCmdProcessorHook::~SubscribeCmdProcessorHook()
{

}

void SubscribeCmdProcessorHook::onStateChange(oplink::ObservableName observableName,
                                              oplink::PropertyName propertyName,
                                              QVariant propertyValue)
{
    m_processor.stateChange(observableName,propertyName,propertyValue);
}
