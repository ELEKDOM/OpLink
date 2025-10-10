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


#include "observablepropertymodel.h"
#include "model/modellogchannel.h"
#include "logger/pflog.h"
#include "observable/property/property.h"

using namespace elekdom::oplink::core::model;
using namespace elekdom::oplink::core;

ObservablePropertyModel::ObservablePropertyModel(const PropertyModelName &modelName,
                                                       const observable::PropertyName &propertyName,
                                                       QVariant::Type valueType):
    plugframe::core::logger::Loggable{s_ModelLogChannel},
    m_modelName{modelName},
    m_propertyName{propertyName},
    m_valueType{valueType}
{
    pfDebug1(logChannel()) << "->ObservablePropertyModel::ObservablePropertyModel, " << modelName << ", " << propertyName << ", " << valueType;

    pfDebug1(logChannel()) << "<-ObservablePropertyModel::ObservablePropertyModel";
}

ObservablePropertyModel::~ObservablePropertyModel()
{

}

observable::Property *ObservablePropertyModel::createProperty(observable::Observable& observable)
{
    return new observable::Property{observable, propertyName(), valueType()};
}
