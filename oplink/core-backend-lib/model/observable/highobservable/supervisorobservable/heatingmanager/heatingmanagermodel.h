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

#ifndef HEATINGMANAGERMODEL_H
#define HEATINGMANAGERMODEL_H

#include "model/observable/highobservable/supervisorobservable/supervisorobservablemodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatingManagerModel : public SupervisorObservableModel
{
public:
    HeatingManagerModel(const ObservableModelName& name);
    ~HeatingManagerModel() override;

protected:
    bool checkBuilderArgs(QspObservableBuilderArgs builderArgs) override;
    ObservableBuilder *createInstance(QspObservableBuilderArgs builderArgs) override;
    bool buildProperties(QspObservableBuilder observableBuilder,
                         QspObservableBuilderArgs builderArgs) override;
    bool buildProcessors(QspObservableBuilder observableBuilder,
                         QspObservableBuilderArgs builderArgs) override;
    void postBuild(QspObservableBuilder observableBuilder,
                   QspObservableBuilderArgs builderArgs) override;
private:
    bool addSetpointProperty(const QspObservableBuilder& observableBuilder,const QString& value);
    bool addTriggerMode(const QspObservableBuilder& observableBuilder,const QString& value);
    bool addDerogatedProperty(const QspObservableBuilder& observableBuilder);
    bool addRoomProperties(const QspObservableBuilder& observableBuilder,
                           const QspObservableBuilderArgs& builderArgs);
    PilotWireControlRoom *createControlRoom(const QspObservableBuilder& observableBuilder,
                                            const QspObservableBuilderArgs& builderArgs,
                                            int roomIdx);
    CommandProcessor *createSetProcessor(Observable& parent);
    CommandProcessor *createRoomProcessor(Observable& parent);
};
}//namespace oplink
#endif // HEATINGMANAGERMODEL_H
