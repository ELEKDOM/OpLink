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


#ifndef DEVICECHANNELSBINDING_H
#define DEVICECHANNELSBINDING_H

#include <QVector>
#include "olcore-backend-lib_export.h"
#include "observable/observablenames.h"

namespace elekdom
{
namespace oplink
{
namespace core
{
namespace infrastructure
{

class OLCORE_BACKEND_LIB_EXPORT DeviceChannelsBinding
{
public:
    DeviceChannelsBinding();

public:
    void insert(int index, const observable::PropertyName& pname);
    const observable::PropertyName& at(int i) const;
    int size() const;

private:
    QVector<observable::PropertyName> m_channels;
};

}//namespace infrastructure
}//namespace core
}//namespace oplink
}//namespace elekdom

#endif // DEVICECHANNELSBINDING_H
