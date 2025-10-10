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


#ifndef PILOTWIRETHERMOSTATCONTROLROOM_H
#define PILOTWIRETHERMOSTATCONTROLROOM_H

#include "pilotwirecontrolroom.h"

namespace elekdom
{
namespace oplink
{
namespace heatingmanager
{

class PilotWireThermostatControlRoom : public PilotWireControlRoom
{
public:
    PilotWireThermostatControlRoom(core::observable::SupervisorObservable& manager,bool wod,bool pd,double max_temp,double threshold);
    ~PilotWireThermostatControlRoom() override;

protected:
    void initAlgo() override;
    void orderForHeaters(const QString &order) override;
    void onStateChangeFromHeaters(const elekdom::oplink::core::observable::ObservableName& observableName,
                                  const elekdom::oplink::core::observable::PropertyName& propertyName,
                                  QVariant propertyValue) override;
    void onStateChangeFromTemperatureSensors(const elekdom::oplink::core::observable::ObservableName& observableName,
                                             const elekdom::oplink::core::observable::PropertyName& propertyName,
                                             QVariant propertyValue) override;
private:
    void regulHeaters();

private:
    double m_max_temp;
    double m_threshold;
    double m_temp_order;
    double m_last_temp;
    quint8 m_last_regulation_order;
};

}//namespace heatingmanager
}//namespace oplink
}//namespace elekdom

#endif // PILOTWIRETHERMOSTATCONTROLROOM_H
