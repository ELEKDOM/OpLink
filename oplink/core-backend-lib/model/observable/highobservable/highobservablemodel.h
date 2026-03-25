#ifndef HIGHOBSERVABLEMODEL_H
#define HIGHOBSERVABLEMODEL_H

#include "model/observable/observablemodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HighObservableModel : public ObservableModel
{
public:
    HighObservableModel(const ObservableModelName& name);
    ~HighObservableModel() override;

protected:
    bool addProperty(const QspObservableBuilder& observableBuilder,
                     const PropertyName& propertyName,
                     const QVariant& value,
                     bool persistentProperty = false); // This flag indicates that the property value must be saved to be restored at next application restarted.
    bool addProperty(const QspObservableBuilder& observableBuilder,
                     const PropertyName& propertyName);
    bool addRunningProperty(const QspObservableBuilder& observableBuilder,bool value);

    bool addTriggerModeProperty(const QspObservableBuilder& observableBuilder,const QString& value);
    bool addSchedulerXmlDefinitionProperty(const QspObservableBuilder& observableBuilder,const QString& value);
};
}//namespace oplink
#endif // HIGHOBSERVABLEMODEL_H
