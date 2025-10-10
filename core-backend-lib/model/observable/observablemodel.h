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

#include <QList>
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"
#include "logger/loggable.h"
#include "model/modelnames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace model
{

class OLCORE_BACKEND_LIB_EXPORT ObservableModel : public plugframe::core::logger::Loggable
{
public:
    ObservableModel(const ObservableModelName& name);
    ~ObservableModel() override;

public:
    const ObservableModelName& modelName() {return m_modelName;}
    void addPropertyModelRef(QspObservablePropertyModel ref);
    void addProcessorModelRef(QspCommandProcessorModel ref);
    observable::QspObservableBuilder buildObservable(QspObservableBuilderArgs builderArgs);

protected:
    virtual bool checkBuilderArgs(QspObservableBuilderArgs builderArgs) = 0;
    virtual observable::ObservableBuilder *createInstance(QspObservableBuilderArgs builderArgs) = 0;
    virtual bool buildProperties(observable::QspObservableBuilder observableBuilder,
                                 QspObservableBuilderArgs builderArgs);
    virtual bool setPropertyMandatoryValues(observable::QspObservableBuilder observableBuilder,
                                            QspObservableBuilderArgs builderArgs);
    virtual void postBuild(observable::QspObservableBuilder observableBuilder,
                           QspObservableBuilderArgs builderArgs);

private:
    bool createProperties(observable::QspObservableBuilder observableBuilder);
    bool buildProcessors(observable::QspObservableBuilder observableBuilder,
                         QspObservableBuilderArgs builderArgs);

private:
    const ObservableModelName         m_modelName;
    QList<QspObservablePropertyModel> m_propertyModelRefs;
    QList<QspCommandProcessorModel>   m_processorModelRefs;
};

}//namespace model
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // OBSERVABLEMODEL_H
