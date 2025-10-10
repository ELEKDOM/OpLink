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


#ifndef GacObservable_H
#define GacObservable_H

#include <QHash>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "observable/observable/observablebuilder.h"
#include "model/modelnames.h"
#include "command/command-names.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{
///
/// \brief The Observable class.
///        Abstraction of an object possessing properties and accepting commands to be applied to its properties.
///        The state of an observable can be tracked.
class OLCORE_BACKEND_LIB_EXPORT Observable : public ObservableBuilder
{

public:
    Observable();
    ~Observable() override;

public:
    const ObservableName& name() const;
    model::ObservableModelName modelId();
    LocalisationName localisation();
    QspProperty property(PropertyName propId) const override;
    void process(command::QspCommand order);
    bool subscribe(ObservableSubscriber *subscriber);
    bool unsubscribe(ObservableSubscriber *subscriber);
    void notifyPropertyValueChange(Property& prop);

protected: // GacObservableBuilder
    void addProperty(Property *newProperty) override;
    void addProcessor(CommandProcessor *newProcessor) override;
    bool setMandatoryPropertyValue(PropertyName propId, QVariant propValue) override;
    void setDevice(infrastructure::QspDevice device) override;
    bool propertyValue(PropertyName propId, QVariant propValue);

private:
    ObservableName                                   m_name;
    QHash<PropertyName, QspProperty>                 m_properties;
    QHash<command::CommandName, QspCommandProcessor> m_processors;
    QspObservableNotifier                            m_notifier;
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // GacObservable_H
