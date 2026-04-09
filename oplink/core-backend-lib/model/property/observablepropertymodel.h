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

#include <QSharedPointer>
#include "logger/loggable.h"
#include "observable/propertyid.h"
#include "model/modelnames.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ObservablePropertyModel : public plugframe::Loggable
{
public:
    ObservablePropertyModel(const PropertyModelName& modelName,
                            const PropertyName& propertyName);
    ~ObservablePropertyModel() override;

public:
    const PropertyModelName& modelName() {return m_modelName;}
    virtual Property *createProperty(Observable& observable);

protected:
    const PropertyName& propertyName(){return m_propertyName;}

private:
    const PropertyModelName m_modelName;
    const PropertyName      m_propertyName;
};
using QspObservablePropertyModel = QSharedPointer<ObservablePropertyModel>;
}//namespace oplink

#endif // OBSERVABLEPROPERTYMODEL_H
