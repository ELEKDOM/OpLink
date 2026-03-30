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

#ifndef HIGHOBSERVABLE_H
#define HIGHOBSERVABLE_H

#include "observable/observable/observable.h"
#include "schedulerhook.h"

namespace oplink
{
/**
 * @brief The HighObservable class
 * @detailsThe HighObservable class represents an Observable whose characteristics are purely logical.
 * It allows the definition of virtual devices.
 * This class allows the optional integration of a sequencing program and a fonctional mode.
 */
class OLCORE_BACKEND_LIB_EXPORT HighObservable : public Observable
{
public:
    HighObservable(const plugframe::QspScheduler& scheduler);
    ~HighObservable() override;

public:
    virtual void onSchedulerEvt(QString evt) = 0;
    virtual void onDailySequencerIndex(int idx);
    virtual void onWeeklySequencer(QString name);
    virtual void onDailySequencer(QString name);
    bool hasPlannedMode();

protected:
    ///
    /// \brief startScheduler
    /// starts the scheduler if it exist.
    /// \param currentEvt
    /// out : currently evt
    ///
    void startScheduler(QString& currentEvt);

    ///
    /// \brief stopScheduler
    ///
    void stopScheduler();

    ///
    /// \brief isOn
    /// \return true if the observable has no running state. The running state value if the observable has a running state.
    ///
    bool isOn();

    ///
    /// \brief isPlannedMode
    /// \return true if the observable have a trigger mode set to "planned"
    ///
    bool isPlannedMode();

    bool isOnDemandMode();

    ///
    /// \brief runningProperty
    /// \param state
    ///
    void runningProperty(const QVariant& state);

    ///
    /// \brief triggerModeProperty
    /// \param mode
    ///
    void triggerModeProperty(const QVariant& mode);



private:
    SchedulerHook m_schedulerSoc;
};
}//namespace oplink
#endif // HIGHOBSERVABLE_H
