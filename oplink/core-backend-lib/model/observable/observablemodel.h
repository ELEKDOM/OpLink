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

#ifndef OBSERVABLEMODEL_H
#define OBSERVABLEMODEL_H

#include <QSharedPointer>
#include <QList>
#include "logger/loggable.h"
#include "model/modelnames.h"
#include "model/property/observablepropertymodel.h"
#include "model/processor/commandprocessormodel.h"
#include "observable/observable/observablebuilder.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT ObservableModel : public plugframe::Loggable
{
public:
    ObservableModel(const ObservableModelName& name);
    ~ObservableModel() override;

public:
    const ObservableModelName& modelName() {return m_modelName;}
    void addPropertyModelRef(oplink::QspObservablePropertyModel ref);
    void addProcessorModelRef(oplink::QspCommandProcessorModel ref);
    oplink::QspObservableBuilder buildObservable(QspObservableBuilderArgs builderArgs);

protected:
    virtual bool checkBuilderArgs(QspObservableBuilderArgs builderArgs) = 0;
    virtual oplink::ObservableBuilder *createInstance(QspObservableBuilderArgs builderArgs) = 0;
    virtual bool buildProperties(oplink::QspObservableBuilder observableBuilder,
                                 QspObservableBuilderArgs builderArgs);
    virtual bool setPropertyMandatoryValues(oplink::QspObservableBuilder observableBuilder,
                                            QspObservableBuilderArgs builderArgs);
    virtual void postBuild(oplink::QspObservableBuilder observableBuilder,
                           QspObservableBuilderArgs builderArgs);

private:
    bool createProperties(oplink::QspObservableBuilder observableBuilder);
    bool buildProcessors(oplink::QspObservableBuilder observableBuilder,
                         QspObservableBuilderArgs builderArgs);

private:
    const ObservableModelName         m_modelName;
    QList<QspObservablePropertyModel> m_propertyModelRefs;
    QList<QspCommandProcessorModel>   m_processorModelRefs;
};
using QspObservableModel = QSharedPointer<ObservableModel>;
}//namespace oplink
#endif // OBSERVABLEMODEL_H
