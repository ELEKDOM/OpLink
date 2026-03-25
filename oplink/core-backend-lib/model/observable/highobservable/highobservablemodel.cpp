#include "highobservablemodel.h"
#include "observable/property/propertyid.h"

oplink::HighObservableModel::HighObservableModel(const ObservableModelName& name):
    ObservableModel{name}
{

}

oplink::HighObservableModel::~HighObservableModel()
{

}

bool oplink::HighObservableModel::addProperty(const QspObservableBuilder &observableBuilder,
                                              const PropertyName &propertyName,
                                              const QVariant& value,
                                              bool persistentProperty)
{
    Property *newProperty;
    bool ret{false};

    newProperty = new Property{observableBuilder->toObservable(), propertyName};
    ret = newProperty != nullptr;
    if (ret)
    {
        observableBuilder->addProperty(newProperty);
        if (!persistentProperty)
        {
            newProperty->value(value);
        }
        else
        {
            // For persistent values, the property value is either:
            //      the last saved value or,
            //      if there is no saved value, the value of the input parameter.

            // To do : create a specifique Bundle and Service for persistent features
            // ...
            newProperty->value(value); // temporary !
        }
    }

    return ret;
}

bool oplink::HighObservableModel::addProperty(const QspObservableBuilder &observableBuilder,
                                              const PropertyName &propertyName)
{
    Property *newProperty;
    bool ret{false};

    newProperty = new Property{observableBuilder->toObservable(), propertyName};
    ret = newProperty != nullptr;
    if (ret)
    {
        observableBuilder->addProperty(newProperty);
    }

    return ret;
}

bool oplink::HighObservableModel::addRunningProperty(const QspObservableBuilder &observableBuilder, bool value)
{
    bool ret;

    ret = addProperty(observableBuilder,
                      PropertyId::P_RUNNING,
                      value,
                      true);
    return ret;
}

bool oplink::HighObservableModel::addTriggerModeProperty(const QspObservableBuilder &observableBuilder, const QString &value)
{
    bool ret;

    ret = addProperty(observableBuilder,
                      PropertyId::P_TRIGGER_MODE,
                      value,
                      true);
    return ret;
}

bool oplink::HighObservableModel::addSchedulerXmlDefinitionProperty(const QspObservableBuilder &observableBuilder, const QString &value)
{
    bool ret;

    ret = addProperty(observableBuilder,
                      PropertyId::P_SCHEDULER_XML_DEF,
                      value,
                      true);
    return ret;
}

