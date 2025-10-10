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


#ifndef HEATINGMANAGER_H
#define HEATINGMANAGER_H

#include <QStringLiteral>
#include "observable/highobservable/schedulableobservable.h"

namespace elekdom
{
namespace oplink
{
namespace heatingmanager
{

class HeatingManager : public core::observable::SchedulableObservable
{
public:
    static QString heaterCategory() {return QStringLiteral("heater");}
    static QString windowSensorCategory() {return QStringLiteral("windowsensor");}
    static QString temperatureSensorCategory() {return QStringLiteral("temperaturesensor");}

public:
    HeatingManager();
    ~HeatingManager() override;

public:
    bool windowSensorState(const QString& roomName, bool allClosed);
    void heaterState(const QString& roomName, QString pwm);

protected:
    void specificInit(engine::service::ObservableServiceInterface *observableService) override;
    void onSchedulerEvt(QString evt) override;

private:
    const QString managerOrder();
    void managerOrder(const QString& order);
    void managerDerogated();
    const QString roomOrder(const QString& roomName);
    void roomOrder(const QString& roomName,const QString& order);
    bool roomDerogated(const QString& roomName);
    void roomDerogated(const QString& roomName,bool flag);
    void processScheduledOrder(const QString& order);
};

}//namespace heatingmanager
}//namespace oplink
}//namespace elekdom

#endif // HEATINGMANAGER_H
