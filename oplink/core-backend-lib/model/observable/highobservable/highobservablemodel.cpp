// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
//
// This file is part of OpLink.
//
// OpLink is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpLink is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//

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

