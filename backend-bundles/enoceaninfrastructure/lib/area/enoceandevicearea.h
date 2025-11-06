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

#ifndef ENOCEANDEVICEAREA_H
#define ENOCEANDEVICEAREA_H

#include "abstract_infrastructure/area/area.h"
#include "packet/format/receivedformat/eeptelegram/eeptelegramformat.h"

class EnoceanDeviceArea : public oplink::Area
{
    Q_OBJECT

public:
    EnoceanDeviceArea(const QString& logChannel,
                      const QString& areaName,
                      QObject *parent);
    ~EnoceanDeviceArea() override;

public slots:
    virtual void onErp1PacketReceived(QspEepTelegramFormat erp1PacketFormat) = 0;

signals:
    void initializeUsb300BaseId();

protected:
    void setGateway(oplink::AreaGateway *gateway) override;
    bool addDevice(const oplink::QspDevice& newDevice) override;

private slots:
    void onDevicesLoaded();
    void onUsb300IdRecovered();

private:
    bool m_devicesLoaded;
    bool m_usb300IdRecovered;
};

#endif // ENOCEANDEVICEAREA_H
