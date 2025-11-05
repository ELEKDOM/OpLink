#ifndef SUBSCRIBECMDPROCESSORHOOK_H
#define SUBSCRIBECMDPROCESSORHOOK_H

#include "observable/observable/observablesubscriber.h"
#include "olconsole_forward.h"

class SubscribeCmdProcessorHook : public oplink::ObservableSubscriber
{
     Q_OBJECT
public:
    SubscribeCmdProcessorHook(SubscribeCmdProcessor& processor);
    ~SubscribeCmdProcessorHook() override;

protected:
    void onStateChange(oplink::ObservableName observableName,
                       oplink::PropertyName propertyName,
                       QVariant propertyValue) override;

private:
    SubscribeCmdProcessor& m_processor;
};

#endif // SUBSCRIBECMDPROCESSORHOOK_H
