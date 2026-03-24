#ifndef HEATINGMANAGERPWMODEL_H
#define HEATINGMANAGERPWMODEL_H

#include "heatingmanagermodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatingManagerPwModel : public HeatingManagerModel
{
public:
    HeatingManagerPwModel(const ObservableModelName& name);
    ~HeatingManagerPwModel() override;
};
}//namespace oplink
#endif // HEATINGMANAGERPWMODEL_H
