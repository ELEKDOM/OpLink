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

#ifndef OBSERVABLEBUILDERSERVICEINTERFACE_H
#define OBSERVABLEBUILDERSERVICEINTERFACE_H

#include "service-int/serviceinterface.h"
#include "observable/observable/observablebuilder.h"
#include "model/observable/observablebuilderargs.h"

namespace oplink
{
class ObservableBuilderServiceInterface : public plugframe::ServiceInterface
{
public:
    static QString serviceName() {return QStringLiteral("ObservableBuilderServiceInterface");}

public:
    ~ObservableBuilderServiceInterface() override {}

public:
    virtual oplink::QspObservableBuilder buildObservable(oplink::QspObservableBuilderArgs builderargs) = 0;
};
}//namespace oplink

#define OlObservableBuilderService_iid "oplink.ObservableBuilderService"
Q_DECLARE_INTERFACE(oplink::ObservableBuilderServiceInterface, OlObservableBuilderService_iid)

#endif // OBSERVABLEBUILDERSERVICEINTERFACE_H
