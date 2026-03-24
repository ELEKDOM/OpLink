#ifndef HEATINGMANAGERPWTMODEL_H
#define HEATINGMANAGERPWTMODEL_H

#include "heatingmanagerpwmodel.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatingManagerPwtModel : public HeatingManagerPwModel
{
public:
    HeatingManagerPwtModel(const ObservableModelName& name);
    ~HeatingManagerPwtModel() override;
};
}//namespace oplink
#endif // HEATINGMANAGERPWTMODEL_H
