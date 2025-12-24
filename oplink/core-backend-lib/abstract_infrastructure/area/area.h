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

#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QSharedPointer>
#include "logger/loggable.h"
#include "abstract_infrastructure/infrastructure-names.h"
#include "abstract_infrastructure/area/areagateway.h"
#include "abstract_infrastructure/device/device.h"
#include "olcore-backend-lib_export.h"

namespace oplink
{
class  OLCORE_BACKEND_LIB_EXPORT Area : public QObject, public plugframe::Loggable
{
    Q_OBJECT

private:
    QString                    m_areaName;
    QspAreaGateway             m_gateway;
    QHash<DeviceId, QspDevice> m_devices;

public:
    Area(const QString& logChannel,
                  const QString& areaName,
                  QObject *parent = nullptr);
    ~Area()override ;

public:
    const QString& name() {return m_areaName;}
    bool haveNoGateway() {return m_gateway.isNull();}

public:
    virtual void setGateway(AreaGateway *gateway);
    virtual bool addDevice(const QspDevice& newDevice);

signals:
    void devicesLoaded();

protected:
    QspDevice getDevice(const DeviceId& id);
    AreaGateway *gateway() {return m_gateway.get();}
    void recoverDevicesState();
};
using QspArea = QSharedPointer<Area>;
}//namespace oplink
#endif // AREA_H
