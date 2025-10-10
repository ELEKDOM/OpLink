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


#ifndef PILOTWIRECONTROLROOM_H
#define PILOTWIRECONTROLROOM_H

#include "observable/highobservable/monitor/grouptowatchalgorithm.h"

namespace elekdom
{
namespace oplink
{
namespace heatingmanager
{

class PilotWireControlRoom : public core::observable::monitoring::GroupToWatchAlgorithm
{
public:
    PilotWireControlRoom(core::observable::SupervisorObservable& manager,bool wod,bool pd);
    ~PilotWireControlRoom() override;

public:
    virtual void orderForHeaters(const QString &order);

protected:
    void initAlgo() override;
    void onStateChange(const elekdom::oplink::core::observable::ObservableName& observableName,
                       const elekdom::oplink::core::observable::PropertyName& propertyName,
                       QVariant propertyValue) override;
    virtual void onStateChangeFromHeaters(const elekdom::oplink::core::observable::ObservableName& observableName,
                                          const elekdom::oplink::core::observable::PropertyName& propertyName,
                                          QVariant propertyValue);
    virtual void onStateChangeFromWindowSensors(const elekdom::oplink::core::observable::ObservableName& observableName,
                                                const elekdom::oplink::core::observable::PropertyName& propertyName,
                                                QVariant propertyValue);
    virtual void onStateChangeFromTemperatureSensors(const elekdom::oplink::core::observable::ObservableName& observableName,
                                                     const elekdom::oplink::core::observable::PropertyName& propertyName,
                                                     QVariant propertyValue);
    virtual void onStateChangeFromUnknownCategory(const elekdom::oplink::core::observable::ObservableName& observableName,
                                                  const elekdom::oplink::core::observable::PropertyName& propertyName,
                                                  QVariant propertyValue);
    bool wod(){return m_wod;}
    bool roomClosed() {return m_roomClosed;}
    void turnComfortHeaters();
    void turnOffHeaters();
    QString convertPWM2str(quint8 pwm);
    void pwmHeater(const QString& oname,const QString& pname,const QString &pwm);

private:
    void turnLastOrderHeaters();

private:
    bool m_wod; // window opening detection flag
    bool m_pd; // presence detection flag
    bool m_roomClosed;
};

}//namespace heatingmanager
}//namespace oplink
}//namespace elekdom

#endif // PILOTWIRECONTROLROOM_H
