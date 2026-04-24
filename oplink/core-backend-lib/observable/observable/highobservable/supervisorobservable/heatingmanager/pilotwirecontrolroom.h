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

#include "observable/observable/highobservable/supervisorobservable/monitor/grouptowatchalgorithm.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT PilotWireControlRoom : public oplink::GroupToWatchAlgorithm
{
public:
    PilotWireControlRoom(oplink::SupervisorObservable& manager,bool wod);
    ~PilotWireControlRoom() override;

public:
    virtual void orderForHeaters(const QString &order);

protected:
    void subscribe() override;
    void unsubscribe() override;
    void onStateChange(oplink::ObservableName observableName,
                       oplink::PropertyName propertyName,
                       QVariant propertyValue) override;
    ///
    /// \brief onStateChangeFromHeaters
    /// Notifies of a change in the pilot wire mode of a heater in the heaters group
    /// \param observableName
    /// \param propertyName
    /// \param propertyValue
    ///
    virtual void onStateChangeFromHeaters(const oplink::ObservableName& observableName,
                                          const oplink::PropertyName& propertyName,
                                          QVariant propertyValue);
    ///
    /// \brief onStateChangeFromWindowSensors
    /// Notifies the change of state of a window opening detector in the detectors group
    /// \param observableName
    /// \param propertyName
    /// \param propertyValue
    ///
    virtual void onStateChangeFromWindowSensors(const oplink::ObservableName& observableName,
                                                const oplink::PropertyName& propertyName,
                                                QVariant propertyValue);
    ///
    /// \brief onStateChangeFromTemperatureSensors
    /// Notifies the change of state of a temperature sensor in the sensors group
    /// \param observableName
    /// \param propertyName
    /// \param propertyValue
    ///
    virtual void onStateChangeFromTemperatureSensors(const oplink::ObservableName& observableName,
                                                     const oplink::PropertyName& propertyName,
                                                     QVariant propertyValue);
    virtual void onStateChangeFromUnknownCategory(const oplink::ObservableName& observableName,
                                                  const oplink::PropertyName& propertyName,
                                                  QVariant propertyValue);
    bool wod(){return m_wod;}
    bool roomClosed() {return m_roomClosed;}
    void turnOffHeaters();
    void pwmHeater(const QString& oname,const QString& pname,const QString &pwm);
    quint8 lastRegulationOrder() {return m_last_regulation_order;}
    void lastRegulationOrder(quint8 lro) {m_last_regulation_order = lro;}

private:
    void turnLastOrderHeaters();

private:
    bool m_wod; // window opening detection flag
    bool m_pd; // presence detection flag.
    bool m_roomClosed;
    quint8 m_last_regulation_order;
};
}//namespace oplink
#endif // PILOTWIRECONTROLROOM_H
