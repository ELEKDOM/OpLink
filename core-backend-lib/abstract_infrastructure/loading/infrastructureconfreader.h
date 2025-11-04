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

#ifndef INFRASTRUCTURECONFREADER_H
#define INFRASTRUCTURECONFREADER_H

#include <QString>
#include <QFile>
#include <QVector>
#include <QXmlStreamReader>
#include "worker/workerthread.h"
#include "logger/loggable.h"
#include "abstract_infrastructure/loading/confreadererror.h"
#include "olcore-backend-lib_export.h"
#include "olcore-backend-lib_forward.h"

namespace oplink
{
class OLCORE_BACKEND_LIB_EXPORT InfrastructureConfReader : public plugframe::WorkerThread,
                                                           public plugframe::Loggable
{
protected:
    inline QString infrastructureNode() { return QStringLiteral("infrastructure"); }
    inline QString areasNode() { return QStringLiteral("areas"); }
    inline QString areaNode() { return QStringLiteral("area"); }
    inline QString gatewayNode() { return QStringLiteral("gateway"); }
    inline QString observablesNode() { return QStringLiteral("observables"); }
    inline QString loadsNode() { return QStringLiteral("loads"); }
    inline QString loadNode() { return QStringLiteral("load"); }
    inline QString actuatorsNode() { return QStringLiteral("actuators"); }
    inline QString actuatorNode() { return QStringLiteral("actuator"); }
    inline QString outputsNode() { return QStringLiteral("outputs"); }
    inline QString outputNode() { return QStringLiteral("output"); }
    inline QString channelsNode() { return QStringLiteral("channels"); }
    inline QString channelNode() { return QStringLiteral("channel"); }
    inline QString sensorsNode() { return QStringLiteral("sensors"); }
    inline QString sensorNode() { return QStringLiteral("sensor"); }
    inline QString nameAttribute() { return QStringLiteral("name"); }
    inline QString protocolAttribute() { return QStringLiteral("protocol"); }
    inline QString observableModelNameAttribute() { return QStringLiteral("model-name"); }
    inline QString localisationAttribute() { return QStringLiteral("localisation"); }
    inline QString deviceIdAttribute() { return QStringLiteral("device-id"); }
    inline QString deviceModelNameAttribute() { return QStringLiteral("device-model-name"); }
    inline QString actuatorPropertyAttribute() { return QStringLiteral("actuator-property"); }
    inline QString actuatedPropertyAttribute() { return QStringLiteral("actuated-property"); }
    inline QString loadAttribute() { return QStringLiteral("load"); }
    inline QString ChannelIdxAttribute() { return QStringLiteral("idx"); }
    inline QString ChannelNameAttribute() { return QStringLiteral("name"); }

public:
    InfrastructureConfReader(const QString& logChannel,
                             oplink::InfrastructureStore& store,
                             plugframe::WorkerSignal *wSignal,
                             const plugframe::QspWorkerArgs& args,
                             QObject *parent = nullptr);
    ~InfrastructureConfReader() override;

protected: // SmfWorkerThread
    bool execWork(plugframe::QspWorkerArgs args) override;
    plugframe::WorkerOuts *getWorkerOuts() override;

protected:
    virtual void extractDataFromGateway(LoadingError& err)= 0;

private:
    void read(QString configFileName, LoadingError& err);
    void readInfrastructure(LoadingError& err);
    void readAreas(LoadingError& err);
    void readArea(LoadingError& err);
    void readGateway(LoadingError& err);
    void readObservables(LoadingError& err);
    void readLoads(LoadingError& err);
    void readLoad(LoadingError& err);
    void readActuators(LoadingError& err);
    void readActuator(LoadingError& err);
    void readDeviceChannels(DeviceChannelsBinding& channels, LoadingError& err);
    void readChannel(DeviceChannelsBinding& channels, LoadingError& err);
    void readActuatorOutputs(ActuatorOutputsBinding& outputs, LoadingError& err);
    void readOutput(ActuatorOutputsBinding& outputs, LoadingError& err);
    void readSensors(LoadingError& err);
    void readSensor(LoadingError& err);

private:
    QFile                m_file;

protected:
    InfrastructureStore& m_store;
    QXmlStreamReader     m_xmlReader;
};
}//namespace oplink
#endif // INFRASTRUCTURECONFREADER_H

