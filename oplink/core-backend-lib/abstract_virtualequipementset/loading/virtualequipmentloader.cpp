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

#include "virtualequipmentloader.h"
#include "abstract_virtualequipementset/virtualequipmentset.h"
#include "observable/observable/highobservable/highobservableconfdocument.h"
#include "logger/pflog.h"

oplink::VirtualEquipmentLoader::VirtualEquipmentLoader(oplink::VirtualEquipmentSet *veSet) :
    m_veSet{veSet}
{
}

oplink::VirtualEquipmentLoader::~VirtualEquipmentLoader()
{

}

void oplink::VirtualEquipmentLoader::confDocument(oplink::HighObservableConfDocument *confDoc)
{
    m_confDoc.reset(confDoc);
}

void oplink::VirtualEquipmentLoader::load(QString fileName)
{
    pfInfo1(m_veSet->logChannel()) << QObject::tr("Chargement d'un fichier de description d'un équipement virtuel : ") << fileName;

    m_builderArgs.reset();
    m_confDoc->load(fileName);

    if (m_confDoc->fileLoaded())
    {
        if (!m_confDoc->browse())
        {
            m_builderArgs.reset();
        }
    }
}

oplink::QspHighObservableBuilderArgs oplink::VirtualEquipmentLoader::builderArgs()
{
    return m_builderArgs;
}

void oplink::VirtualEquipmentLoader::builderArgs(HighObservableBuilderArgs *newBuilderArgs)
{
    m_builderArgs.reset(newBuilderArgs);
}

oplink::PropertyRefBuilderArgs *oplink::VirtualEquipmentLoader::createPropertyRef(const QString &observableName,
                                                                                  const QString &propertyNameName)
{
    return new oplink::PropertyRefBuilderArgs{observableName,propertyNameName};
}

