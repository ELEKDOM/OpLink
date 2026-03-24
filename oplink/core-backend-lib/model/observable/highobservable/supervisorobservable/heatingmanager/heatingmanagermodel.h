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
};
}//namespace oplink
#endif // HEATINGMANAGERMODEL_H
