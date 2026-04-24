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

#ifndef HIGHOBSERVABLEBUILDERARGS_H
#define HIGHOBSERVABLEBUILDERARGS_H

#include "model/observable/observablebuilderargs.h"
#include "scheduler/scheduler.h"
#include "service-int/observableserviceinterface.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT PropertyRefBuilderArgs
{
public:
    PropertyRefBuilderArgs(const QString& observableName,
                           const QString& propertyName) :
        m_observableName{observableName},
        m_propertyName{propertyName} {};
public:
    QString m_observableName;
    QString m_propertyName;
};
using QspPropertyRefBuilderArgs = QSharedPointer<PropertyRefBuilderArgs>;

class OLCORE_BACKEND_LIB_EXPORT HighObservableBuilderArgs : public ObservableBuilderArgs
{
public:
    HighObservableBuilderArgs(const ObservableName& observableName,
                              const ObservableModelName& observableModelName,
                              const LocalisationName& observableLocalisation,
                              bool activated = true);
    ~HighObservableBuilderArgs() override;

public:
    bool                        m_activated;
    plugframe::QspScheduler     m_schedul;
    QString                     m_schedulXmlText;
    ObservableServiceInterface *m_observableService;
};
using QspHighObservableBuilderArgs = QSharedPointer<HighObservableBuilderArgs>;
}//namespace oplink
#endif // HIGHOBSERVABLEBUILDERARGS_H
