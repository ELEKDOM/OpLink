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

#ifndef HIGHOBSERVABLEMODEL_H
#define HIGHOBSERVABLEMODEL_H

#include "model/observable/observablemodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HighObservableModel : public ObservableModel
{
public:
    HighObservableModel(const ObservableModelName& name);
    ~HighObservableModel() override;

protected:
    bool addProperty(const QspObservableBuilder& observableBuilder,
                     const PropertyName& propertyName,
                     const QVariant& value,
                     bool persistentProperty = false); // This flag indicates that the property value must be saved to be restored at next application restarted.
    bool addProperty(const QspObservableBuilder& observableBuilder,
                     const PropertyName& propertyName);
    bool addRunningProperty(const QspObservableBuilder& observableBuilder,bool value);

    bool addTriggerModeProperty(const QspObservableBuilder& observableBuilder,const QString& value);
    bool addSchedulerXmlDefinitionProperty(const QspObservableBuilder& observableBuilder,const QString& value);
};
}//namespace oplink
#endif // HIGHOBSERVABLEMODEL_H
