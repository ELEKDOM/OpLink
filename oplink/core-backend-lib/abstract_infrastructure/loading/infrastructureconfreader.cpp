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

#include <QObject>
#include "infrastructureconfreader.h"
#include "worker/workerargs.h"
#include "logger/pflog.h"
#include "abstract_infrastructure/loading/infrastructureloaderargs.h"
#include "abstract_infrastructure/loading/infrastructurestore.h"
#include "abstract_infrastructure/loading/actuatoroutputsbinding.h"
#include "abstract_infrastructure/loading/devicechannelsbinding.h"

oplink::InfrastructureConfReader::InfrastructureConfReader(const QString& logChannel,
                                                   InfrastructureStore &store,
                                                   plugframe::WorkerSignal *wSignal,
                                                   const plugframe::QspWorkerArgs &args,
                                                   QObject *parent):
    plugframe::WorkerThread{wSignal, args, parent},
    plugframe::Loggable{logChannel},
    m_store{store}
{

}

oplink::InfrastructureConfReader::~InfrastructureConfReader()
{

}

bool oplink::InfrastructureConfReader::execWork(plugframe::QspWorkerArgs args)
{
    bool ret;
    oplink::QspDeviceInfrastructureLoaderArgs argsLoader{args.dynamicCast<oplink::InfrastructureLoaderArgs>()};
    LoadingError err;

    read(argsLoader->m_configFile, err);
    ret = err == LoadingError::NoError;

    sleep(1); // Caution !! This delay (1ns) is to ensure that the USB key identifier
              //            is retrieved before the thread ends !!
    return ret;
}

plugframe::WorkerOuts *oplink::InfrastructureConfReader::getWorkerOuts()
{
    return m_store.readFinished(m_ret);
}

void oplink::InfrastructureConfReader::read(QString configFileName, oplink::LoadingError& err)
{
    err = oplink::LoadingError::NoError;

    pfInfo3(logChannel()) << "xml parser : file = " << configFileName;

    m_file.setFileName(configFileName);
    if (m_file.open(QFile::ReadOnly | QFile::Text))
    {
        m_xmlReader.setDevice(&m_file);
        if (m_xmlReader.readNextStartElement())
        {
            readInfrastructure(err);
        }
        else
        {
            err = oplink::LoadingError::FileError;
            pfWarning7(logChannel()) << QObject::tr("Le ficher %1 ne semble pas être un fichier de description d'une infrastructure").arg(configFileName) << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
        m_file.close();
    }
    else
    {
        err = oplink::LoadingError::FileError;
        pfWarning7(logChannel()) << QObject::tr("Impossible d'ouvrir le fichier %1").arg(configFileName) << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readInfrastructure(oplink::LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == infrastructureNode())
    {
        if (m_store.checkInfrastructureName(m_xmlReader.attributes().value(protocolAttribute()).toString()))
        {
            readAreas(err);
        }
        else
        {
            err = oplink::LoadingError::StructuralError;
            pfWarning7(logChannel()) << QObject::tr("Le nom de l'infrastructure ne correspond pas à celui défini par le bundle") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Le noeud racine doit se nommer <infrastructure>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readAreas(LoadingError& err)
{   
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == areasNode())
        {
            while (m_xmlReader.readNextStartElement()  && LoadingError::NoError == err)
            {
                readArea(err);
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("La première partie de déclaration des zones doit être le noeud <areas>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud pour la définition des zones") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readArea(oplink::LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == areaNode())
    {
        QString areaName{m_xmlReader.attributes().value(nameAttribute()).toString()};

        pfInfo3(logChannel()) << "xml parser : areaName = " << areaName;

        if (m_store.addArea(areaName))
        {
            readGateway(err);
            if (oplink::LoadingError::NoError == err)
            {
                readObservables(err);
                if (oplink::LoadingError::NoError == err)
                {
                    m_xmlReader.readNextStartElement(); // go back to areas node
                }
            }
        }
        else
        {
            err = oplink::LoadingError::StructuralError;
            pfWarning7(logChannel()) << QObject::tr("Echec de création d'une nouvelle zone dans l'infrastructure %1").arg(areaName) << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Le noeud de déclaration d'une zone doit se nommer <area>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readGateway(LoadingError& err)
{
    if (m_xmlReader.readNextStartElement() && m_xmlReader.name() == gatewayNode())
    {
        extractDataFromGateway(err);
        if (oplink::LoadingError::NoError == err)
        {
            m_xmlReader.readNextStartElement(); // go back to area node
        }
    }
    else
    {
       err = oplink::LoadingError::XmlError;
       pfWarning7(logChannel()) << QObject::tr("La passerelle doit être définie par un noeud <gateway>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readObservables(LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == observablesNode())
        {
            readLoads(err);
            if (oplink::LoadingError::NoError == err)
            {
                readActuators(err);
                if (oplink::LoadingError::NoError == err)
                {
                    readSensors(err);
                    if (oplink::LoadingError::NoError == err)
                    {
                        m_xmlReader.readNextStartElement(); // go back to area node
                    }
                }
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("Dans une zone, les participants doivent être déclarés dans le noeud observables") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud pour la définition des observables") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readLoads(LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == loadsNode())
        {
            while (m_xmlReader.readNextStartElement()  && LoadingError::NoError == err)
            {
                readLoad(err);
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("La première partie de déclaration des observables doit être le noeud <loads>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud pour la définition des loads") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readLoad(LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == loadNode())
    {
        QString loadName{m_xmlReader.attributes().value(nameAttribute()).toString()};
        QString observableModelName{m_xmlReader.attributes().value(observableModelNameAttribute()).toString()};
        QString localisation{m_xmlReader.attributes().value(localisationAttribute()).toString()};

        pfInfo3(logChannel()) << "xml parser : loadName = " << loadName << ", observableModelName = "  << observableModelName << ", localisation = " << localisation;

        if (! m_store.addLoad(loadName, observableModelName, localisation))
        {
            err = oplink::LoadingError::StructuralError;
            pfWarning7(logChannel()) << QObject::tr("Echec de création de la charge %1 (modèle %2 localisation %3)").arg(loadName, observableModelName, localisation) << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
        else
        {
            m_xmlReader.readNextStartElement(); // go back to loads node
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Le noeud de déclaration d'une charge doit se nommer <load>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readActuators(LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == actuatorsNode())
        {
            while (m_xmlReader.readNextStartElement() && LoadingError::NoError == err)
            {
                readActuator(err);
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("La deuxième partie de déclaration des observables doit être le noeud <actuators>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud pour la définition des actuators") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readActuator(oplink::LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == actuatorNode())
    {
        QString actuatorName{m_xmlReader.attributes().value(nameAttribute()).toString()};
        QString observableModelName{m_xmlReader.attributes().value(observableModelNameAttribute()).toString()};
        QString deviceId{m_xmlReader.attributes().value(deviceIdAttribute()).toString()};
        QString deviceModelName{m_xmlReader.attributes().value(deviceModelNameAttribute()).toString()};
        QString localisation{m_xmlReader.attributes().value(localisationAttribute()).toString()};

        oplink::ActuatorOutputsBinding outputsBinding;
        oplink::DeviceChannelsBinding deviceChannelsBinding;

        pfInfo3(logChannel()) << "xml parser : actuatorName = " << actuatorName << ", observableModelName = "  << observableModelName << ", deviceId = " << deviceId <<", deviceModelName = " << deviceModelName << ", localisation = " << localisation;

        readDeviceChannels(deviceChannelsBinding, err);
        if (oplink::LoadingError::NoError == err)
        {
            readActuatorOutputs(outputsBinding, err);
            if (oplink::LoadingError::NoError == err)
            {
                if (!m_store.addActuator(actuatorName,
                                         observableModelName,
                                         deviceId,
                                         deviceModelName,
                                         localisation,
                                         outputsBinding,
                                         deviceChannelsBinding))
                {
                    err = oplink::LoadingError::StructuralError;
                    pfWarning7(logChannel()) << QObject::tr("Echec de création de l'actionneur %1 (modèle %2 deviceId %3 deviceModel %4 localisation %5)").arg(actuatorName, observableModelName, deviceId, deviceModelName, localisation) << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
                }
                else
                {
                    m_xmlReader.readNextStartElement(); // go back to actuators node
                }
            }
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Le noeud de déclaration d'un actionneur doit se nommer <actuator>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readDeviceChannels(oplink::DeviceChannelsBinding &channels,
                                                          oplink::LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == channelsNode())
        {
            while (m_xmlReader.readNextStartElement() && oplink::LoadingError::NoError == err)
            {
                readChannel(channels, err);
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("Un device doit déclarer le noeud <channels>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud <channels> dans la déclaration du device") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readChannel(oplink::DeviceChannelsBinding &channels,
                                                   oplink::LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == channelNode())
    {
        int channelIdx{m_xmlReader.attributes().value(ChannelIdxAttribute()).toInt()};
        QString channelName{m_xmlReader.attributes().value(ChannelNameAttribute()).toString()};

        pfInfo3(logChannel()) << "xml parser : channelIdx = " << channelIdx << ", channelName = " << channelName;

        channels.insert(channelIdx, channelName);
        m_xmlReader.readNextStartElement(); // go back to channels node
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Un canal doit être déclaré dans un noeud <channel>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readActuatorOutputs(oplink::ActuatorOutputsBinding& outputs,
                                                           oplink::LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == outputsNode())
        {
            while (m_xmlReader.readNextStartElement() && LoadingError::NoError == err)
            {
                readOutput(outputs, err);
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("Un actuator doit déclarer le noeud <outputs>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud <outputs> dans la déclaration de l'actuator") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readOutput(oplink::ActuatorOutputsBinding &outputs,
                                                  oplink::LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == outputNode())
    {
        QString actuator_property{m_xmlReader.attributes().value(actuatorPropertyAttribute()).toString()};
        QString load{m_xmlReader.attributes().value(loadAttribute()).toString()};
        QString actuated_property{m_xmlReader.attributes().value(actuatedPropertyAttribute()).toString()};
        oplink::ActuatorOutput output{actuator_property, load, actuated_property};

        pfInfo3(logChannel()) << "xml parser : actuator output, actuatorProperty = " << actuator_property << ", load = " << load << ", loadProperty = " << actuated_property;

        outputs.append(output);
        m_xmlReader.readNextStartElement(); // go back to outputs node
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Une sortie d'actuator doit être déclarée dans un noeud <output>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readSensors(oplink::LoadingError& err)
{
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.isStartElement() && m_xmlReader.name() == sensorsNode())
        {
            while (m_xmlReader.readNextStartElement() && oplink::LoadingError::NoError == err)
            {
                readSensor(err);
            }
        }
        else
        {
            err = oplink::LoadingError::XmlError;
            pfWarning7(logChannel()) << QObject::tr("La troisième partie de déclaration des observables doit être le noeud <sensors>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Il n'y a pas de noeud pour la définition des sensors") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}

void oplink::InfrastructureConfReader::readSensor(oplink::LoadingError& err)
{
    if (m_xmlReader.isStartElement() && m_xmlReader.name() == sensorNode())
    {
        QString sensorName{m_xmlReader.attributes().value(nameAttribute()).toString()};
        QString observableModelName{m_xmlReader.attributes().value(observableModelNameAttribute()).toString()};
        QString deviceId{m_xmlReader.attributes().value(deviceIdAttribute()).toString()};
        QString deviceModelName{m_xmlReader.attributes().value(deviceModelNameAttribute()).toString()};
        QString localisation{m_xmlReader.attributes().value(localisationAttribute()).toString()};

        pfInfo3(logChannel()) << "xml parser : sensorName = " << sensorName << ", observableModelName = "  << observableModelName << ", deviceId = " << deviceId <<", deviceModelName = " << deviceModelName << ", localisation = " << localisation;

        oplink::DeviceChannelsBinding deviceChannelsBinding;

        readDeviceChannels(deviceChannelsBinding, err);
        if (oplink::LoadingError::NoError == err)
        {
            if (!m_store.addSensor(sensorName,
                                   observableModelName,
                                   deviceId,
                                   deviceModelName,
                                   localisation,
                                   deviceChannelsBinding))
            {
                err = oplink::LoadingError::XmlError;
                pfWarning7(logChannel()) << QObject::tr("Echec de création du capteur %1 (modèle %2 deviceId %3 deviceModel %4 localisation %5)").arg(sensorName, observableModelName, deviceId, deviceModelName, localisation) << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
            }
            else
            {
                m_xmlReader.readNextStartElement(); // go back to sensors node
            }
        }
    }
    else
    {
        err = oplink::LoadingError::XmlError;
        pfWarning7(logChannel()) << QObject::tr("Le noeud de déclaration d'un capteur doit se nommer <sensor>") << QObject::tr(" xml, ligne : ") << m_xmlReader.lineNumber();
    }
}



