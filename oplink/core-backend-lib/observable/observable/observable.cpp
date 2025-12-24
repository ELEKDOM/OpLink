// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#include <QCoreApplication>
#include "observable.h"
#include "observable/observable/observablenotifier.h"
#include "observable/property/property.h"
#include "observable/property/propertyid.h"
#include "observable/processor/commandprocessor.h"
#include "command/command.h"
#include "logger/pflog.h"

oplink::Observable::Observable():
    m_name{""},
    m_notifier{new oplink::ObservableNotifier}
{
    m_notifier->moveToThread(QCoreApplication::instance()->thread());
}

oplink::Observable::~Observable()
{
}

const oplink::ObservableName& oplink::Observable::name() const
{
    return m_name;
}

oplink::ObservableModelName oplink::Observable::modelId()
{
    oplink::QspProperty propertyModelId{m_properties.value(oplink::PropertyId::P_MODEL)};
    return (propertyModelId->value()).toString();
}

oplink::LocalisationName oplink::Observable::localisation()
{
    QspProperty propertyLocalisation{m_properties.value(oplink::PropertyId::P_LOCALISATION)};
    return (propertyLocalisation->value()).toString();
}

oplink::QspProperty oplink::Observable::property(PropertyName propId) const
{
    return m_properties.value(propId);
}

void oplink::Observable::process(oplink::QspCommand order)
{
    const oplink::CommandName& cmdName{order->name()};

    if (m_processors.contains(cmdName))
    {
        oplink::QspCommandProcessor selected{m_processors.value(cmdName)};

        if (!selected->acceptCmd(order))
        {
            pfWarning3(logChannel()) << QObject::tr("%1, erreur de cible dans la commande sur %2").arg(order->observable(), name());
        }
    }
    else
    {
        pfWarning3(logChannel()) << QObject::tr("commande non acceptée par %1").arg(name());
    }
}

bool oplink::Observable::subscribe(oplink::ObservableSubscriber *subscriber)
{
    return m_notifier->subscribe(subscriber);
}

bool oplink::Observable::unsubscribe(oplink::ObservableSubscriber *subscriber)
{
    return m_notifier->unsubscribe(subscriber);
}

void oplink::Observable::notifyPropertyValueChange(oplink::Property &prop)
{
    m_notifier->notifyPropertyValueChange(name(),
                                          prop.name(),
                                          prop.value());
}

void oplink::Observable::addProperty(oplink::Property *newProperty)
{
    oplink::QspProperty newProp{newProperty};

    m_properties.insert(newProp->name(), newProp);
}

void oplink::Observable::addProcessor(oplink::CommandProcessor *newProcessor)
{
    oplink::QspCommandProcessor newProc{newProcessor};
    m_processors.insert(newProc->cmdName(), newProc);
}

bool oplink::Observable::setMandatoryPropertyValue(oplink::PropertyName propId, QVariant propValue)
{
    bool ret {propertyValue(propId, propValue)};

    if (propId == oplink::PropertyId::P_NAME)
    {
        m_name = propValue.toString();
    }
    return ret;
}

void oplink::Observable::setDevice(oplink::QspDevice device)
{
    Q_UNUSED(device)
}

bool oplink::Observable::propertyValue(oplink::PropertyName propId,QVariant propValue)
{
    bool ret{false};

    if (m_properties.contains(propId))
    {
        oplink::QspProperty selected{property(propId)};

        if (!selected.isNull())
        {
            selected->value(propValue);
            ret = true;
        }
    }

    return ret;
}
