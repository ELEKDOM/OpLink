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


#ifndef OBSERVABLEBUILDER_H
#define OBSERVABLEBUILDER_H

#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "logger/loggable.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace observable
{
///
/// \brief The ObservableBuilder class.
///        Defining the construction interface of an observable.
class OLCORE_BACKEND_LIB_EXPORT ObservableBuilder : public plugframe::core::logger::Loggable
{
public:
    ObservableBuilder();
    ~ObservableBuilder() override;

public:
    virtual void addProperty(Property *newProperty) = 0;
    virtual void addProcessor(CommandProcessor *newProcessor) = 0;
    virtual bool setMandatoryPropertyValue(PropertyName propId, QVariant propValue) = 0;
    virtual void setDevice(infrastructure::QspDevice device) = 0;
    virtual QspProperty property(PropertyName propId) const = 0;
    virtual infrastructure::QspDevice device(); // Only Sensor and Actuator have device !
    virtual void initScheduler(); // Only VirtualEquipment have scheduler !
    Observable& toObservable();
};

}//namespace observable
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEBUILDER_H
