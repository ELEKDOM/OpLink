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


#ifndef OBSERVABLEPROPERTYMODEL_H
#define OBSERVABLEPROPERTYMODEL_H

#include <QVariant>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "logger/loggable.h"
#include "observable/observablenames.h"
#include "model/property/propertymodelnames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT ObservablePropertyModel : public plugframe::core::logger::Loggable
{
public:
    ObservablePropertyModel(const PropertyModelName& modelName,
                               const observable::PropertyName& propertyName,
                               QVariant::Type valueType);
    ~ObservablePropertyModel() override;

public:
    const PropertyModelName& modelName() {return m_modelName;}
    virtual observable::Property *createProperty(observable::Observable& observable);

protected:
    const observable::PropertyName& propertyName(){return m_propertyName;}
    QVariant::Type valueType(){return m_valueType;}

private:
    const PropertyModelName         m_modelName;
    const observable::PropertyName  m_propertyName;
    QVariant::Type                     m_valueType;
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEPROPERTYMODEL_H
