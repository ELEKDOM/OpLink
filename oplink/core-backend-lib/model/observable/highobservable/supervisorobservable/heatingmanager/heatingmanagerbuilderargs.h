// Copyright (C) 2026 ELEKDOM Christophe Mars c.mars@elekdom.fr
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

#ifndef HEATINGMANAGERBUILDERARGS_H
#define HEATINGMANAGERBUILDERARGS_H

#include <QVector>
#include "model/observable/highobservable/supervisorobservable/supervisorobservablebuilderargs.h"
#include "observable/observable/highobservable/supervisorobservable/heatingmanager/heatingmanagerloaderhook.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT HeatedRoomBuilderArgs
{
public:
    HeatedRoomBuilderArgs(const QString& name,
                          bool wod):
        m_name{name},
        m_wod{wod} {};

public:
    QString                            m_name;
    bool                               m_wod;
    QVector<QspPropertyRefBuilderArgs> m_heaters;
    QVector<QspPropertyRefBuilderArgs> m_windowSensors;
    QVector<QspPropertyRefBuilderArgs> m_tempSensors;
};
using QspHeatedRoomBuilderArgs = QSharedPointer<HeatedRoomBuilderArgs>;

class OLCORE_BACKEND_LIB_EXPORT HeatingManagerBuilderArgs : public SupervisorObservableBuilderArgs
{
public:
    HeatingManagerBuilderArgs(const ObservableName& observableName,
                              const ObservableModelName& observableModelName,
                              const LocalisationName& observableLocalisation,
                              HeatingManagerLoaderHook::ControlType controlType,
                              bool activated);
    ~HeatingManagerBuilderArgs() override;

public:
    double                                m_max_temp, m_threshold;
    bool                                  m_setPointScheduled;
    QString                               m_setPoint;
    HeatingManagerLoaderHook::ControlType m_controlType;
    QVector<QspHeatedRoomBuilderArgs>     m_rooms;
};
using QspHeatingManagerBuilderArgs = QSharedPointer<HeatingManagerBuilderArgs>;
}//namespace oplink
#endif // HEATINGMANAGERBUILDERARGS_H
